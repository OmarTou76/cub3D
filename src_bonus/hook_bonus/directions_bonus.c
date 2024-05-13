/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:20:40 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 19:28:51 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
