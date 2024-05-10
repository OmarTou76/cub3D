/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:25:15 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/11 00:40:58 by omar             ###   ########.fr       */
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
	player->pos.next = NULL;
	if (player == NULL)
		return (NULL);
	if (!find_player_position(map, &player->pos.x, &player->pos.y))
		return (free(player), NULL);
	player_direction = map[player->pos.y][player->pos.x];
	player->delta_x = 0;
	player->delta_y = 0;
	if (player_direction == 'N')
		player->angle = 90;
	else if (player_direction == 'S')
		player->angle = 270;
	else if (player_direction == 'W')
		player->angle = 180;
	else if (player_direction == 'E')
		player->angle = 0;
	return (player);
}

int	get_max_width(char **map)
{
	size_t	i;
	size_t	max_width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max_width)
			max_width = ft_strlen(map[i]);
		i++;
	}
	return (max_width);
}

void	store_map_data(t_game **game)
{
	(*game)->map.width = get_max_width((*game)->map.map);
	(*game)->map.height = get_map_height((*game)->map.map);
	if ((*game)->map.height > (*game)->map.width)
		(*game)->map.tile_size = (int)round(WINDOW_HEIGHT
				/ (*game)->map.height);
	else
		(*game)->map.tile_size = (int)round(WINDOW_WIDTH / (*game)->map.width);
	(*game)->map.padding_y = (WINDOW_HEIGHT - ((*game)->map.height
				* (*game)->map.tile_size)) / 2;
	(*game)->map.padding_x = (WINDOW_WIDTH - ((*game)->map.width
				* (*game)->map.tile_size)) / 2;
	(*game)->map.player_size = (int)round((*game)->map.tile_size / 3);
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
			(*game)->map.map = node_to_map(&tmp);
			break ;
		}
		tmp = tmp->next;
	}
	(*game)->player = get_info_player((*game)->map.map);
	store_map_data(game);
}
