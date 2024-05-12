/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:11:17 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 14:01:49 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_collision_point(t_vec *door, t_wall target, t_game *game)
{
	int		player_x;
	int		player_y;
	float	fract_x;
	float	fract_y;

	player_y = game->player->img_player->instances[0].y / game->map.tile_size
		- game->map.padding_y / game->map.tile_size;
	player_x = game->player->img_player->instances[0].x / game->map.tile_size
		- game->map.padding_x / game->map.tile_size;
	fract_x = fmod(target.collision_x, 1.0f);
	fract_y = fmod(target.collision_y, 1.0f);
	if (game->map.map[(int)(target.collision_y)][(int)(target.collision_x)]
		== 'D')
	{
		door->y = (int)(target.collision_y);
		door->x = (int)(target.collision_x);
	}
	else if (player_x < target.collision_x && fract_x >= 0.97 && game->map.map
		[(int)(target.collision_y)][(int)ceil(target.collision_x)] == 'D')
	{
		door->y = (int)(target.collision_y);
		door->x = (int)ceil(target.collision_x);
	}
	else if (player_y < target.collision_y && fract_y >= 0.97 && game->map.map
		[(int)ceil(target.collision_y)][(int)(target.collision_x)] == 'D')
	{
		door->y = (int)ceil(target.collision_y);
		door->x = (int)(target.collision_x);
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
	// write(1, "\a", 1); // "Bruit de l'arme"
}

void	shoot_animation(void *param)
{
	t_game			*game;
	unsigned int	delay;

	game = (t_game *)param;
	if (game->player->moves)
		delay = 1;
	else
		delay = 10;
	if (game->animation.start)
	{
		game->animation.gun_delay++;
		if (game->animation.gun_delay >= delay)
		{
			if (game->animation.gun_frame == 1)
				break_wall(game);
			game->animation.gun_frame = (game->animation.gun_frame + 1) % 4;
			game->animation.gun_delay = 0;
			game->animation.pistol[0]->enabled = false;
			game->animation.pistol[1]->enabled = false;
			game->animation.pistol[2]->enabled = false;
			game->animation.pistol[3]->enabled = false;
			game->animation.pistol[game->animation.gun_frame]->enabled = true;
			if (game->animation.gun_frame == 0)
				game->animation.start = false;
		}
	}
}

void	shoot(t_game *game)
{
	game->animation.gun_delay = 0;
	game->animation.gun_frame = 0;
	game->animation.start = true;
}
