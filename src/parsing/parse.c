#include "../../include/cub3D.h"

char	*trimed_path(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	i += 3;
	while (line[i] && line[i] == ' ')
		i++;
	return (line + i);
}

void	get_textures_paths(t_game **game, char *line)
{
	if (trim_compare(line, "NO ", 3) == 0)
		(*game)->paths->NO = trimed_path(line);
	else if (trim_compare(line, "EA ", 3) == 0)
		(*game)->paths->EA = trimed_path(line);
	else if (trim_compare(line, "WE ", 3) == 0)
		(*game)->paths->WE = trimed_path(line);
	else if (trim_compare(line, "SO ", 3) == 0)
		(*game)->paths->SO = trimed_path(line);
}

void	save_colors(unsigned int colors[3], char **colors_val)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		colors[i] = ft_atoi(colors_val[i]);
		i++;
	}
}

void	get_colors(t_game **game, char *line)
{
	int		i;
	char	**spl;

	if (trim_compare(line, "C ", 2) == 0 || trim_compare(line, "F ", 2) == 0)
	{
		i = 2;
		while (line[i] && line[i] == ' ')
			i++;
		spl = ft_split(line + i, ',');
		if (trim_compare(line, "C ", 2) == 0)
			save_colors((*game)->colors->ceiling, spl);
		else
			save_colors((*game)->colors->floor, spl);
		i = 0;
		while (spl[i])
		{
			free(spl[i]);
			i++;
		}
		free(spl);
	}
}

void	store_data(t_game **game, t_node *node)
{
	t_node *tmp;

	tmp = node;
	(*game) = malloc(sizeof(t_game));
	(*game)->paths = malloc(sizeof(t_texture_paths));
	(*game)->colors = malloc(sizeof(t_colors));
	while (tmp)
	{
		get_textures_paths(game, tmp->line);
		get_colors(game, tmp->line);
		tmp = tmp->next;
	}
}