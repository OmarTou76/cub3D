/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:23:32 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/02 15:22:24 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void update_player_position(t_game *game, int new_y, int new_x)
{
	if ((game->s_map.map[new_y / game->s_map.tile_size][new_x / game->s_map.tile_size] != '1') && game->s_map.map[(new_y + game->s_map.player_size) / game->s_map.tile_size][(new_x + game->s_map.player_size) / game->s_map.tile_size] != '1')
	{
		game->player->img_player->instances[0].y = new_y;
		game->player->img_player->instances[0].x = new_x;
	}
}

void go_forward(t_game *game)
{
	int new_x = game->player->img_player->instances[0].x + game->player->delta_x;
	int new_y = game->player->img_player->instances[0].y + game->player->delta_y;
	update_player_position(game, new_y, new_x);
}

void go_backward(t_game *game)
{
	int new_x = game->player->img_player->instances[0].x - game->player->delta_x;
	int new_y = game->player->img_player->instances[0].y - game->player->delta_y;
	update_player_position(game, new_y, new_x);
}

void go_left(t_game *game)
{
	float radian_angle;

	radian_angle = game->player->angle * M_PI / 180.0;
	int new_x = game->player->img_player->instances[0].x;
	int new_y = game->player->img_player->instances[0].y;
	new_x += (int)round(PLAYER_SPEED * cos(radian_angle + M_PI / 2.0));
	new_y -= (int)round(PLAYER_SPEED * sin(radian_angle + M_PI / 2.0));
	update_player_position(game, new_y, new_x);
}

void go_right(t_game *game)
{
	float radian_angle;

	radian_angle = game->player->angle * M_PI / 180.0;
	int new_x = game->player->img_player->instances[0].x;
	int new_y = game->player->img_player->instances[0].y;
	new_x += (int)round(PLAYER_SPEED * cos(radian_angle - M_PI / 2.0));
	new_y -= (int)round(PLAYER_SPEED * sin(radian_angle - M_PI / 2.0));
	update_player_position(game, new_y, new_x);
}
