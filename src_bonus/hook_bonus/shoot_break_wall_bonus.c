/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_break_wall_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:47:58 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 17:49:56 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	calculate_player_coordinates(t_game *game, int *player_x,
		int *player_y)
{
	*player_x = game->player->img_player->instances[0].x / game->map.tile_size
		- game->map.padding_x / game->map.tile_size;
	*player_y = game->player->img_player->instances[0].y / game->map.tile_size
		- game->map.padding_y / game->map.tile_size;
}

static void	calculate_fractions(float collision_x, float collision_y,
		float *fract_x, float *fract_y)
{
	*fract_x = fmod(collision_x, 1.0f);
	*fract_y = fmod(collision_y, 1.0f);
}

static void	get_collision_point(t_vec *door, t_wall wall, t_game *game)
{
	int		player_x;
	int		player_y;
	float	fract_x;
	float	fract_y;

	calculate_player_coordinates(game, &player_x, &player_y);
	calculate_fractions(wall.collision_x, wall.collision_y, &fract_x, &fract_y);
	if (game->map.map[(int)(wall.collision_y)][(int)(wall.collision_x)] == 'D')
	{
		door->y = (int)(wall.collision_y);
		door->x = (int)(wall.collision_x);
	}
	else if (player_x < wall.collision_x && fract_x >= 0.97 && game->map.map
		[(int)(wall.collision_y)][(int)ceil(wall.collision_x)] == 'D')
	{
		door->y = (int)(wall.collision_y);
		door->x = (int)ceil(wall.collision_x);
	}
	else if (player_y < wall.collision_y && fract_y >= 0.97 && game->map.map
		[(int)ceil(wall.collision_y)][(int)(wall.collision_x)] == 'D')
	{
		door->y = (int)ceil(wall.collision_y);
		door->x = (int)(wall.collision_x);
	}
}

void	break_wall(t_game *game)
{
	t_wall	target;
	t_vec	collision;

	target.crack = false;
	target.column_angle = game->player->angle;
	compute_distance_and_select_wall(game, &target);
	if (target.crack)
	{
		get_collision_point(&collision, target, game);
		game->map.map[collision.y][collision.x] = '0';
		fill_by_pixel(game->map, (collision.y * game->map.tile_size),
			(collision.x * game->map.tile_size), ft_pixel(150, 150, 150, 0x90));
		raycast(game);
	}
	write(1, "\a", 1);
}
