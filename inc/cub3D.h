/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:11:28 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 14:29:43 by ymeziane         ###   ########.fr       */
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

# define TILE_SIZE 64

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

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_map
{
	char			**map;
	unsigned int	height;
	unsigned int	width;
	t_point			player;
}					t_map;

typedef struct s_player
{
	t_point			pos;
	double			delta_x;
	double			delta_y;
	double			angle;
	mlx_image_t		*img;
}					t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	t_texture_paths	*paths;
	t_colors		*colors;
	t_map			s_map;
	t_player		*player;
}					t_game;

typedef struct s_lines
{
	char			*line;
	struct s_lines	*next;
}					t_lines;

typedef struct s_vec
{
	int				y;
	int				x;
	struct s_vec	*next;
}					t_vec;

///////////////////////////////////////////
//	CHECKER FOLDER

//	CHECKER
char				**node_to_map(t_lines **node);
int					check_input(char const *progname, char const *filename,
						int argc);
int					is_map_start(char *line);
int					is_valid_data(t_lines *node);
//	FIELDS_CHECKER
void				init_fields(t_fields *f);
int					trim_compare(char *base, char *to_compare, size_t size);
int					check_fields(char *line, t_fields *fields);
//	MAP_CHECKER
int					is_valid_map(t_lines **node);
//	SPACES_CHECKER
int					is_spaces_outside(t_vec **vecs, char **m, int y, int x);
///////////////////////////////////////////
// UTILS FOLDER

// LIST UTILS
t_lines				*save_data(char const *filename);
void				free_nodes(t_lines *node);
void				add_vec(t_vec **vecs, int y, int x);
bool				has_vec(t_vec *vec, int y, int x);
void				free_vecs(t_vec *vecs);

// PRINT UTILS
void				print_data(t_game *game);
void				print_lines(t_lines *tmp);
///////////////////////////////////////////
// PARSE
void				store_data(t_game **game, t_lines *node);
///////////////////////////////////////////
// DRAW MAP 2D
int					draw_map2d(t_game *game);
///////////////////////////////////////////
// FREE
void				free_game(t_game *game);
///////////////////////////////////////////
// HOOK
void				ft_moove_player(mlx_key_data_t key, void *param);

#endif