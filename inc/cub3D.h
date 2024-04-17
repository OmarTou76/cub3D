/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:11:28 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/17 14:33:00 by omar             ###   ########.fr       */
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

# define TILE_SIZE 48
# define MAP_TILE_SIZE TILE_SIZE / 2
# define PLAYER_SIZE MAP_TILE_SIZE / 2
# define PLAYER_SPEED TILE_SIZE / 5

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
	mlx_image_t			*image_map;
}						t_map;

typedef struct s_direction_line
{
	mlx_image_t			*img_line;
	int					length;
	int					start_x;
	int					start_y;
	int					end_x;
	int					end_y;
	int					delta_x;
	int					delta_y;
	int					step_x;
	int					step_y;
	int					error;
	int					error2;
}						t_direction_line;

typedef struct s_player
{
	t_point				pos;
	double				delta_x;
	double				delta_y;
	double				angle;
	mlx_image_t			*img_player;
	t_direction_line	*line;
}						t_player;

typedef struct s_game
{
	mlx_t				*mlx;
	t_texture_paths		*paths;
	t_colors			*colors;
	t_map				s_map;
	t_player			*player;
	mlx_image_t			*img_view_3d;
	mlx_image_t			*wall_image;
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

// MAP_PLAYER
void					store_data(t_game **game, t_lines *node);
// TEXTURE_COLOR
void					get_colors(t_game **game, char *line);
void					get_textures_paths(t_game **game, char *line);
///////////////////////////////////////////
// UTILS FOLDER

// LIST
t_lines					*save_data(char const *filename);
void					add_vec(t_vec **vecs, int y, int x);
bool					has_vec(t_vec *vec, int y, int x);
float					radian_to_degree(float angle);

// PRINT
void					print_data(t_game *game);
void					print_lines(t_lines *tmp);
///////////////////////////////////////////
// DRAW_MAP FOLDER

// COLOR
void					color_img(mlx_image_t *img, uint32_t color, int width,
							int height);
void					color_line(mlx_image_t *img, uint32_t color,
							t_game *game, double angle);
int32_t					ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
// DRAW MAP 2D
void					draw_map2d(t_game *game);
void					initialize_line_data(t_direction_line *line,
							double angle, unsigned int line_height);
void					draw_3d_col(t_game *game, double angle,
							float wall_height);
///////////////////////////////////////////
// FREE
void					free_game(t_game *game);
void					free_nodes(t_lines *node);
void					free_vecs(t_vec *vecs);
///////////////////////////////////////////
// HOOK
void					ft_moove_player(mlx_key_data_t key, void *param);

#endif
