/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:25:15 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 16:14:05 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*trimed_path(char *line)
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

static void	get_textures_paths(t_game **game, char *line)
{
	if (trim_compare(line, "NO ", 3) == 0)
		(*game)->paths->no = trimed_path(line);
	else if (trim_compare(line, "EA ", 3) == 0)
		(*game)->paths->ea = trimed_path(line);
	else if (trim_compare(line, "WE ", 3) == 0)
		(*game)->paths->we = trimed_path(line);
	else if (trim_compare(line, "SO ", 3) == 0)
		(*game)->paths->so = trimed_path(line);
}

static void	save_colors(unsigned int colors[3], char **colors_val)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		colors[i] = ft_atoi(colors_val[i]);
		i++;
	}
}

static void	get_colors(t_game **game, char *line)
{
	int		i;
	char	**spl;

	if (trim_compare(line, "C ", 2) == 0 || trim_compare(line, "F ", 2) == 0)
	{
		i = 0;
		while (line[i] && line[i] == ' ')
			i++;
		i += 2;
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

size_t	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

t_player	*get_info_player(char **map)
{
	int			i;
	int			j;
	t_player	*player;

	player = NULL;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				player = malloc(sizeof(t_player));
				if (player == NULL)
					return (NULL);
				player->pos.x = j;
				player->pos.y = i;
				player->delta_x = 0;
				player->delta_y = 0;
				if(map[i][j] == 'N')
					player->angle = 270;
				else if(map[i][j] == 'S')
					player->angle = 90;
				else if(map[i][j] == 'W')
					player->angle = 180;
				else if(map[i][j] == 'E')
					player->angle = 0;
				return (player);
			}
			j++;
		}
		i++;
	}
	if (player != NULL)
		free(player);
	return (NULL);
}

void	store_data(t_game **game, t_lines *node)
{
	t_lines	*tmp;

	tmp = node;
	(*game) = malloc(sizeof(t_game));
	(*game)->paths = malloc(sizeof(t_texture_paths));
	(*game)->colors = malloc(sizeof(t_colors));
	while (tmp)
	{
		get_textures_paths(game, tmp->line);
		get_colors(game, tmp->line);
		if (ft_strlen(tmp->line) && is_map_start(tmp->line))
		{
			(*game)->s_map.map = node_to_map(&tmp);
			break ;
		}
		tmp = tmp->next;
	}
	(*game)->s_map.width = ft_strlen((*game)->s_map.map[0]);
	(*game)->s_map.height = get_map_height((*game)->s_map.map);
	(*game)->player = get_info_player((*game)->s_map.map);
}
