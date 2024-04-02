#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_fields
{
	int				NO;
	int				SO;
	int				WE;
	int				EA;
	int				F;
	int				C;
	int				is_ok;
}					t_fields;

typedef struct s_colors
{
	unsigned int	floor[3];
	unsigned int	ceiling[3];
}					t_colors;

typedef struct s_texture_paths
{
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
}					t_texture_paths;

typedef struct s_game
{
	t_texture_paths	*paths;
	t_colors		*colors;
	char			**map;
}					t_game;

typedef struct s_node
{
	char			*line;
	struct s_node	*next;
}					t_node;

typedef struct s_vec
{
	int				x;
	int				y;
	int				z;
}					t_vec;

// LIBFT
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strlen(const char *str);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strdup(const char *src);
char				*get_next_line(int fd);
char				*ft_strchr(char *s, int c);
int					ft_isspace(int c);
char				**ft_split(char const *s, char sep);
int					ft_atoi(const char *str);
int					trim_compare(char *base, char *to_compare, size_t size);

// LIST UTILS
t_node				*save_data(char const *filename);
void				free_nodes(t_node *node);

// PARSING
int					is_valid_ext(char const *filename);
void				init_fields(t_fields *f);
int					check_fields(char *line, t_fields *fields);
int					is_map_start(char *line);
char				**node_to_map(t_node **node);
int					is_valid_data(t_node *node);
int					is_valid_map(t_node **node);
void				store_data(t_game **game, t_node *node);

#endif