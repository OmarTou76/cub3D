/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:25:15 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/12 15:31:35 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

static int	find_player_position(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				*y = i;
				*x = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

t_player	*get_info_player(char **map)
{
	t_player	*player;
	char		player_direction;

	player = malloc(sizeof(t_player));
	player->line = malloc(sizeof(t_direction_line));
	if (player == NULL || player->line == NULL)
		return (NULL);
	if (!find_player_position(map, &player->pos.x, &player->pos.y))
		return (free(player), NULL);
	player_direction = map[player->pos.y][player->pos.x];
	player->delta_x = 0;
	player->delta_y = 0;
	if (player_direction == 'N')
		player->angle = 270;
	else if (player_direction == 'S')
		player->angle = 90;
	else if (player_direction == 'W')
		player->angle = 180;
	else if (player_direction == 'E')
		player->angle = 0;
	return (player);
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
