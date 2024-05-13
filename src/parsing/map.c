/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:25:15 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 01:49:10 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static size_t	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
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
