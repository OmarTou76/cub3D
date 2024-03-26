#include "../../include/cub3D.h"

int	is_valid_ext(char const *filename)
{
	char	*ext;

	ext = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if (!ext || ft_strncmp(ext, ".cub", ft_strlen(ext)) != 0)
		return (0);
	return (1);
}

int	has_all_textures(t_node **node)
{
	int		textures[4] = {0};
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = *node;
	while (tmp && i < 4)
	{
		if (!ft_strncmp(tmp->line, "NO ", 3))
			textures[0]++;
		else if (!ft_strncmp(tmp->line, "SO ", 3))
			textures[1]++;
		else if (!ft_strncmp(tmp->line, "WE ", 3))
			textures[2]++;
		else if (!ft_strncmp(tmp->line, "EA ", 3))
			textures[3]++;
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < 4 && textures[i] == 1)
		i++;
	if (i != 4 || ft_strlen(tmp->line) != 0)
		return (0);
	*node = tmp;
	return (1);
}

int	has_colors(t_node **node)
{
	int		textures[2] = {0};
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = *node;
	while (tmp && i < 2)
	{
		if (!ft_strncmp(tmp->line, "F ", 2))
			textures[0]++;
		else if (!ft_strncmp(tmp->line, "C ", 2))
			textures[1]++;
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < 2 && textures[i] == 1)
		i++;
	if (i != 2 || ft_strlen(tmp->line) != 0)
		return (0);
	*node = tmp;
	return (1);
}

int	is_valid_map(t_node *node)
{
	t_node *tmp;
	int i;

	i = 0;
	tmp = node;
	while (tmp)
	{
		printf("%d:[%s]\n", i, tmp->line);
		if ((!ft_strncmp(tmp->line, "NO ", 3) || !ft_strncmp(tmp->line, "SO ",
					3) || !ft_strncmp(tmp->line, "WE ", 3)
				|| !ft_strncmp(tmp->line, "EA ", 3)) && !has_all_textures(&tmp))
			return ((1));
		if ((!ft_strncmp(tmp->line, "F ", 2) || !ft_strncmp(tmp->line, "C ", 2))
			&& !has_colors(&tmp))
			return (1);
		tmp = tmp->next;
		i++;
	}
	return (1);
}