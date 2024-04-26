/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:44:36 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/26 19:04:31 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	r(float nb)
{
	return (int)round(nb);
}

static void	get_wall_img(t_wall *wall, t_game *game)
{
	wall->img = game->textures.south;
}

static void	compute_distance_and_select_wall(t_game *game, t_wall *wall)
{
	t_direction_line	line;
	float				theta;
	float				y;
	float				x;
	float				step_y;
	float				step_x;

	line.start_x = game->player->img_player->instances[0].x * TILE_FACTOR;
	line.start_y = game->player->img_player->instances[0].y * TILE_FACTOR;
	y = line.start_y;
	x = line.start_x;
	theta = ((-wall->column_angle * M_PI) / 180.0);
	step_y = sin(theta) * 0.2;
	step_x = cos(theta) * 0.2;
	while (true)
	{
		if (game->s_map.map[r(y) / TILE_SIZE][r(x) / TILE_SIZE] == '1')
		{
			wall->collision_y = y / TILE_SIZE;
			wall->collision_x = x / TILE_SIZE;
			get_wall_img(wall, game);
			wall->distance = (sqrt(pow(x - line.start_x, 2) + pow(y
							- line.start_y, 2)));
			return ;
		}
		x += step_x;
		y += step_y;
	}
}

void	get_wall(t_game *game, t_wall *wall, float left_angle, int index)
{
	int column_count;

	column_count = game->img_view_3d->width;
	wall->column_angle = left_angle + (index * FOV / column_count);
	compute_distance_and_select_wall(game, wall);
	wall->height = (game->img_view_3d->height / wall->distance) * (TILE_SIZE);
}