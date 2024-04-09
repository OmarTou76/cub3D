/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 14:57:46 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_turn_player(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key.key == MLX_KEY_Z)
	{
		game->player->pos.x += game->player->delta_x;
		game->player->pos.y += game->player->delta_y;
	}
	if (key.key == MLX_KEY_S)
	{
		game->player->pos.x -= game->player->delta_x;
		game->player->pos.y -= game->player->delta_y;
	}
	if (key.key == MLX_KEY_Q)
	{
		game->player->angle -= 0.1;
		if (game->player->angle < 0)
			game->player->angle += (2 * M_PI);
		game->player->delta_x = cos(game->player->angle) * 5;
		game->player->delta_y = sin(game->player->angle) * 5;
	}
	if (key.key == MLX_KEY_D)
	{
		game->player->angle += game->player->delta_y;
		if (game->player->angle < 2 * M_PI)
			game->player->angle -= (2 * M_PI);
		game->player->delta_x = cos(game->player->angle) * 5;
		game->player->delta_y = sin(game->player->angle) * 5;
	}
}

void	ft_moove_player(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key.action == MLX_PRESS || key.action == MLX_REPEAT)
	{
		if (key.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		if (key.key == MLX_KEY_UP)
			game->player->img_player->instances[0].y -= TILE_SIZE / 10;
		if (key.key == MLX_KEY_DOWN)
			game->player->img_player->instances[0].y += TILE_SIZE / 10;
		if (key.key == MLX_KEY_LEFT)
			game->player->img_player->instances[0].x -= TILE_SIZE / 10;
		if (key.key == MLX_KEY_RIGHT)
			game->player->img_player->instances[0].x += TILE_SIZE / 10;
		if (key.key == MLX_KEY_Z || key.key == MLX_KEY_S || key.key == MLX_KEY_Q
			|| key.key == MLX_KEY_D)
			ft_turn_player(key, param);
	}
}
