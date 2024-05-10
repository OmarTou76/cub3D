/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:11:28 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/11 00:59:58 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_HEIGHT 800
# define WINDOW_WIDTH 1000
# define FOV 60.0
# define TILE_SIZE 30
# define TILE_FACTOR 1
# define MAP_TILE_SIZE (TILE_SIZE / TILE_FACTOR)
# define PLAYER_SIZE (MAP_TILE_SIZE) / 3
# define PLAYER_SPEED 4
# define ROTATE_SPEED 4

typedef struct s_fields
{
	int				no;
	int				so;
	int				we;
	int				ea;
	int				f;
	int				c;
	int				is_ok;
}					t_fields;

typedef struct s_colors
{
	unsigned int	floor[3];
	unsigned int	ceiling[3];
}					t_colors;

typedef struct s_texture_paths
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
}					t_texture_paths;

typedef struct s_rays_map
{
	mlx_image_t		*img_line;
	float			length;
}					t_rays_map;

typedef struct s_map
{
	char			**map;
	unsigned int	height;
	unsigned int	width;
	int				padding_y;
	int				padding_x;
	int				tile_size;
	int				player_size;
	mlx_image_t		*img_map;
	t_rays_map		rays;
}					t_map;

typedef struct s_ray_direction
{
	float			angle_radian;
	float			final_collision_dist;
	float			start_x;
	float			start_y;
	float			end_x;
	float			end_y;
	float			step_x;
	float			step_y;
}					t_ray_direction;

typedef struct s_vec
{
	int				y;
	int				x;
	struct s_vec	*next;
}					t_vec;

typedef struct s_player
{
	t_vec			pos;
	float			delta_x;
	float			delta_y;
	float			angle;
	mlx_image_t		*img_player;
}					t_player;

typedef struct s_textures
{
	mlx_image_t		*north;
	mlx_image_t		*south;
	mlx_image_t		*east;
	mlx_image_t		*west;
	mlx_image_t		*crack;
	mlx_image_t		*pistol[4];
	mlx_image_t		*reticle;
}					t_textures;

typedef struct s_animation
{
	unsigned int	gun_delay;
	unsigned int	gun_frame;
	bool			start;
	mlx_image_t		*crack;
	mlx_image_t		*pistol[4];
	mlx_image_t		*reticle;
}					t_animation;

typedef struct s_game
{
	mlx_t			*mlx;
	t_texture_paths	*paths;
	t_colors		*colors;
	t_map			map;
	t_player		*player;
	mlx_image_t		*img_view_3d;
	t_textures		textures;
	t_animation		animation;
}					t_game;

typedef struct s_lines
{
	char			*line;
	struct s_lines	*next;
}					t_lines;

typedef struct s_wall
{
	float			column_angle;
	float			distance;
	float			height;
	float			collision_y;
	float			collision_x;
	float			last_collision_y;
	float			last_collision_x;
	bool			crack;
	mlx_image_t		*img;
}					t_wall;

///////////////////////////////////////////
//	CHECKER FOLDER

//	CHECKER
char				**node_to_map(t_lines **node);
int					check_input(char const *progname, char const *filename,
						int argc);
int					is_map_start(char *line);
int					is_valid_data(t_lines *node);
//	FIELDS
void				init_fields(t_fields *f);
int					trim_compare(char *base, char *to_compare, size_t size);
int					check_fields(char *line, t_fields *fields);
//	MAP
int					is_valid_map(t_lines **node);
//	SPACES
int					is_spaces_outside(t_vec **vecs, char **m, int y, int x);
///////////////////////////////////////////
//	PARSING FOLDER

//	MAP_PLAYER
void				store_data(t_game **game, t_lines *node);
//	TEXTURE_COLOR
void				get_colors(t_game **game, char *line);
void				get_textures_paths(t_game **game, char *line);
///////////////////////////////////////////
//	UTILS FOLDER

//	LIST
t_lines				*save_data(char const *filename);
void				add_vec(t_vec **vecs, int y, int x);
bool				has_vec(t_vec *vec, int y, int x);
//	PRINT
void				print_data(t_game *game);
void				print_lines(t_lines *tmp);
//	COLOR
uint32_t			convert_rgba_to_argb(uint32_t rgba);
int32_t				ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void				color_img(mlx_image_t *img, uint32_t color, int width,
						int height);
///////////////////////////////////////////
//	DRAW_MAP FOLDER

//	INIT GAME
void				fill_by_pixel(t_map map, int posY, int posX, int32_t color);
// DRAW MAP 2D
bool				init_game(t_game *game);

///////////////////////////////////////////
//	FREE
void				free_game(t_game *game);
void				free_nodes(t_lines *node);
void				free_vecs(t_vec *vecs);
void				delete_images(t_game *game);
///////////////////////////////////////////
//	HOOK FOLDER

//	MAP
void				init_and_draw_line(mlx_t *mlx, t_game *game);
void				init_and_draw_map(t_game *game);
void				display_map(t_game *game);
void				refresh_pixels_line(mlx_image_t *img_line);
//	DIRECTIONS
void				hook_moves(void *param);
void				calcul_deltas(t_game **g);
void				shoot(t_game *game);
void				shoot_animation(void *param);
void				listen_mouse_event(t_game *game);
// MOVES
void				go_forward(t_game *game);
void				go_backward(t_game *game);
void				go_left(t_game *game);
void				go_right(t_game *game);
//	RAYCAST FOLDER
//	RAYCAST
uint32_t			convert_rgba_to_argb(uint32_t rgba);
int32_t				ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void				raycast(t_game *game);

//	RAYCAST UTILS
void				init_ray_properties(t_ray_direction *ray, t_game *game,
						t_wall *wall);
bool				is_cracked_wall(t_wall *wall, t_game *game,
						int texture_index);

//	TEXTURE
bool				init_and_load_textures(t_game *game);
//	WALL
void				compute_distance_and_select_wall(t_game *game,
						t_wall *wall);
void				get_wall(t_game *game, t_wall *wall, float left_angle,
						int index);
///////////////////////////////////////////

#endif
