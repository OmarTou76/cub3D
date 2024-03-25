/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:59:36 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 20:00:20 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
