/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:11:28 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 16:30:10 by ymeziane         ###   ########.fr       */
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

# define WINDOW_HEIGHT 900
# define WINDOW_WIDTH 900
# define FOV 60.0
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
	float			normalize_dist;
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
	bool			moves;
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
	bool			mouse_event;
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

//	DATA
int					check_input(char const *progname, char const *filename,
						int argc);
int					is_map_start(char *line);
int					is_valid_data(t_lines *node);
//	FIELDS
int					trim_compare(char *base, char *to_compare, size_t size);
int					check_fields(char *line, t_fields *fields);
//	MAP UTILS
int					check_lines(char **m);
int					check_columns(char **m);
int					check_start_pos(char **map);
//	MAP
int					is_valid_map(t_lines **node);
//	RGB DATA
int					is_valid_rgb_data(char *line);
//	SPACES
bool				has_vec(t_vec *vec, int y, int x);
int					is_spaces_outside(t_vec **vecs, char **m, int y, int x);
///////////////////////////////////////////
//	HOOK FOLDER

//	DIRECTIONS
void				go_forward(t_game *game);
void				go_backward(t_game *game);
void				go_left(t_game *game);
void				go_right(t_game *game);
//	MAP
void				refresh_pixels_line(mlx_image_t *img_line);
void				display_map(t_game *game);
// MLX HOOK
void				key_hook(mlx_key_data_t key, void *param);
void				loop_hook(void *param);
// MOVES
void				listen_mouse_event(t_game *game);
void				update_player_position(t_game *game, int new_y, int new_x);
void				hook_moves(void *param);
// ROTATE
void				rotate_right(t_game *game);
void				rotate_left(t_game *game);
// SHOOT ANIMATION
void				shoot_animation(void *param);
void				shoot(t_game *game);
//	SHOOT BREAK WALL
void				break_wall(t_game *game);
///////////////////////////////////////////
//	INIT AND DRAW FOLDER

//	DRAW MAP
void				fill_by_pixel(t_map map, int posY, int posX, int32_t color);
void				init_and_draw_line(mlx_t *mlx, t_game *game);
void				init_and_draw_map(t_game *game);
// GAME
bool				init_and_draw_game(t_game *game);
char				**node_to_map(t_lines **node);
///////////////////////////////////////////
//	PARSING FOLDER

//	DATA
void				store_data(t_game **game, t_lines *node);
//	MAP
int					get_max_width(char **map);
void				store_map_data(t_game **game);
// PLAYER
t_player			*get_info_player(char **map);
//	TEXTURE_COLOR
void				get_textures_paths(t_game **game, char *line);
void				get_colors(t_game **game, char *line);
///////////////////////////////////////////
//	RAYCAST FOLDER

//	RAYCAST UTILS
bool				is_cracked_wall(t_wall *wall, t_game *game,
						int texture_index);
void				init_ray_properties(t_ray_direction *ray, t_game *game,
						t_wall *wall);
//	RAYCAST
void				raycast(t_game *game);
//	TEXTURE
bool				init_and_load_textures(t_game *game);
//	WALL UTILS
int					get_border_wall_index(t_wall *wall, float player_y,
						float player_x);
int					has_texture_conflict(float fract_y, float fract_x);
void				save_wall_properties(t_game *game, t_wall *wall,
						t_ray_direction *ray);
//	WALL
void				compute_distance_and_select_wall(t_game *game,
						t_wall *wall);
void				get_wall(t_game *game, t_wall *wall, float left_angle,
						int index);
///////////////////////////////////////////
//	UTILS FOLDER

//	COLOR
uint32_t			convert_rgba_to_argb(uint32_t rgba);
int32_t				ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void				color_img(mlx_image_t *img, uint32_t color, int width,
						int height);
//	FREE
void				free_game(t_game *game);
void				free_nodes(t_lines *node);
void				free_vecs(t_vec *vecs);
void				delete_images(t_game *game);
//	LIST
t_lines				*save_data(char const *filename);
///////////////////////////////////////////

#endif
