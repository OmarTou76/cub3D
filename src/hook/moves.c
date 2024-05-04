/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:23:32 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/04 01:13:10 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	update_player_position(t_game *game, int new_y, int new_x)
{
	int	paddingY;
	int	paddingX;
	int	start_player_y;
	int	start_player_x;
	int	index_y;
	int	index_x;

	paddingY = (WINDOW_HEIGHT - game->s_map.img_map->height) / 2;
	paddingX = (WINDOW_WIDTH - game->s_map.img_map->width) / 2;
	start_player_y = (int)round(((float)new_y / (float)game->s_map.tile_size
				- (float)paddingY / (float)game->s_map.tile_size));
	start_player_x = (int)round(((float)new_x / (float)game->s_map.tile_size
				- (float)paddingX / (float)game->s_map.tile_size));
	index_y = (int)floor(((float)new_y / (float)game->s_map.tile_size
				- (float)paddingY / (float)game->s_map.tile_size));
	index_x = (int)floor(((float)new_x / (float)game->s_map.tile_size
				- (float)paddingX / (float)game->s_map.tile_size));
	if ((game->s_map.map[index_y][index_x] != '1'
			&& game->s_map.map[index_y][index_x] != 'D')
		&& ( game->s_map.map[(int)start_player_y][(int)start_player_x] != '1'
			&& game->s_map.map[(int)start_player_y][(int)start_player_x] != 'D')
		&& (game->s_map.map[index_y][(int)start_player_x] != '1'
			&& game->s_map.map[index_y][(int)start_player_x] != 'D')
		&& (game->s_map.map[(int)start_player_y][index_x] != '1'
			&& game->s_map.map[(int)start_player_y][index_x] != 'D'))
	{
		game->player->img_player->instances[0].y = new_y;
		game->player->img_player->instances[0].x = new_x;
	}
}

void	go_forward(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player->img_player->instances[0].x + game->player->delta_x;
	new_y = game->player->img_player->instances[0].y + game->player->delta_y;
	update_player_position(game, new_y, new_x);
}

void	go_backward(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player->img_player->instances[0].x - game->player->delta_x;
	new_y = game->player->img_player->instances[0].y - game->player->delta_y;
	update_player_position(game, new_y, new_x);
}

void	go_left(t_game *game)
{
	float	radian_angle;
	int		new_x;
	int		new_y;

	radian_angle = game->player->angle * M_PI / 180.0;
	new_x = game->player->img_player->instances[0].x;
	new_y = game->player->img_player->instances[0].y;
	new_x += (int)round(PLAYER_SPEED * cos(radian_angle + M_PI / 2.0));
	new_y -= (int)round(PLAYER_SPEED * sin(radian_angle + M_PI / 2.0));
	update_player_position(game, new_y, new_x);
}

void	go_right(t_game *game)
{
	float	radian_angle;
	int		new_x;
	int		new_y;

	radian_angle = game->player->angle * M_PI / 180.0;
	new_x = game->player->img_player->instances[0].x;
	new_y = game->player->img_player->instances[0].y;
	new_x += (int)round(PLAYER_SPEED * cos(radian_angle - M_PI / 2.0));
	new_y -= (int)round(PLAYER_SPEED * sin(radian_angle - M_PI / 2.0));
	update_player_position(game, new_y, new_x);
}
