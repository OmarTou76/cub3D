/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:11:28 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/04 14:39:17 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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

typedef struct s_game
{
	t_texture_paths	*paths;
	t_colors		*colors;
	char			**map;
}					t_game;

typedef struct s_lines
{
	char			*line;
	struct s_lines	*next;
}					t_lines;

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
///////////////////////////////////////////
// UTILS FOLDER

// LIST UTILS
t_lines				*save_data(char const *filename);
void				free_nodes(t_lines *node);
///////////////////////////////////////////
// PARSE
void				store_data(t_game **game, t_lines *node);

#endif