/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otourabi <otourabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:11:28 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/06 16:18:39 by otourabi         ###   ########.fr       */
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
# define PLAYER_SPEED 6
# define ROTATE_SPEED 6

typedef struct s_fields
{
	int					no;
	int					so;
	int					we;
	int					ea;
	int					f;
	int					c;
	int					is_ok;
}						t_fields;

typedef struct s_colors
{
	unsigned int		floor[3];
	unsigned int		ceiling[3];
}						t_colors;

typedef struct s_texture_paths
{
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
}						t_texture_paths;

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_map
{
	char				**map;
	unsigned int		height;
	unsigned int		width;
	int					tile_size;
	int					player_size;
	mlx_image_t			*img_map;
}						t_map;

typedef struct s_direction_line
{
	mlx_image_t			*img_line;
	float				length;
	float				start_x;
	float				start_y;
	float				end_x;
	float				end_y;
	float				delta_x;
	float				delta_y;
	float				step_x;
	float				step_y;
	float				error;
	float				error2;
}						t_direction_line;

typedef struct s_player
{
	t_point				pos;
	float				delta_x;
	float				delta_y;
	float				angle;
	mlx_image_t			*img_player;
	t_direction_line	*line;
}						t_player;

typedef struct s_textures
{
	mlx_image_t			*north;
	mlx_image_t			*south;
	mlx_image_t			*east;
	mlx_image_t			*west;
	mlx_image_t			*crack;
	mlx_image_t			*pistol[4];
	mlx_image_t			*reticle;
	t_point				center_texture;
}						t_textures;

typedef struct s_game
{
	mlx_t				*mlx;
	t_texture_paths		*paths;
	t_colors			*colors;
	t_map				s_map;
	t_player			*player;
	mlx_image_t			*img_view_3d;
	t_textures			textures;
	unsigned int		gun_delay;
	unsigned int		gun_frame;
	bool				shoot;
}						t_game;

typedef struct s_lines
{
	char				*line;
	struct s_lines		*next;
}						t_lines;

typedef struct s_vec
{
	int					y;
	int					x;
	struct s_vec		*next;
}						t_vec;

typedef struct s_wall
{
	float				column_angle;
	float				distance;
	float				height;
	mlx_image_t			*img;
	float				collision_y;
	float				collision_x;
	bool				crack;
}						t_wall;

///////////////////////////////////////////
//	CHECKER FOLDER

//	CHECKER
char					**node_to_map(t_lines **node);
int						check_input(char const *progname, char const *filename,
							int argc);
int						is_map_start(char *line);
int						is_valid_data(t_lines *node);
//	FIELDS
void					init_fields(t_fields *f);
int						trim_compare(char *base, char *to_compare, size_t size);
int						check_fields(char *line, t_fields *fields);
//	MAP
int						is_valid_map(t_lines **node);
//	SPACES
int						is_spaces_outside(t_vec **vecs, char **m, int y, int x);
///////////////////////////////////////////
//	PARSING FOLDER

//	MAP_PLAYER
void					store_data(t_game **game, t_lines *node);
//	TEXTURE_COLOR
void					get_colors(t_game **game, char *line);
void					get_textures_paths(t_game **game, char *line);
///////////////////////////////////////////
//	UTILS FOLDER

//	LIST
t_lines					*save_data(char const *filename);
void					add_vec(t_vec **vecs, int y, int x);
bool					has_vec(t_vec *vec, int y, int x);
float					radian_to_degree(float angle);
//	PRINT
void					print_data(t_game *game);
void					print_lines(t_lines *tmp);
//	COLOR
uint32_t				convert_rgba_to_argb(uint32_t rgba);
int32_t					ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void					color_img(mlx_image_t *img, uint32_t color, int width,
							int height);
///////////////////////////////////////////
//	DRAW_MAP FOLDER

//	INIT GAME
void					draw_line_on_map(t_game *game, float angle);
void					fill_by_pixel(t_map map, int posY, int posX,
							int32_t color);
// DRAW MAP 2D
bool					init_game(t_game *game);

// RAYCAST
uint32_t				convert_rgba_to_argb(uint32_t rgba);
float					get_wall_height_and_draw_line(t_game *game,
							float left_angle, int index);
void					raycast(t_game *game);
float					radian_to_degree(float angle);
int32_t					ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
///////////////////////////////////////////
//	FREE
void					free_game(t_game *game);
void					free_nodes(t_lines *node);
void					free_vecs(t_vec *vecs);
void					delete_images(t_game *game);
///////////////////////////////////////////
//	HOOK FOLDER

//	MAP
void					display_map(t_game *game);
void					refresh_pixels_line(mlx_image_t *img_line);
//	DIRECTIONS
void					hook_moves(void *param);
void					calcul_deltas(t_game **g);
void					shoot(t_game *game);
void					shoot_animation(void *param);
void					listen_mouse_event(t_game *game);
// MOVES
void					go_forward(t_game *game);
void					go_backward(t_game *game);
void					go_left(t_game *game);
void					go_right(t_game *game);
//	RAYCAST FOLDER
//	RAYCAST
void					raycast(t_game *game);
//	TEXTURE
bool					init_and_load_textures(t_game *game);
//	WALL
void					compute_distance_and_select_wall(t_game *game,
							t_wall *wall, bool center_texture);
void					get_wall(t_game *game, t_wall *wall, float left_angle,
							int index);
///////////////////////////////////////////

#endif