#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
}					t_game;

typedef struct s_node
{
	char			*line;
	struct s_node	*next;
}					t_node;

// LIBFT
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strlen(const char *str);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*get_next_line(int fd);
char				*ft_strchr(char *s, int c);

// LIST UTILS
t_node				*save_data(char const *filename);

// PARSING
int					is_valid_ext(char const *filename);
int					is_valid_map(t_node *node);

#endif