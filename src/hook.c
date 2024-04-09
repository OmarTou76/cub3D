/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 22:01:46 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_turn_player(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key.key == MLX_KEY_W)
	{
		game->player->pos.x += game->player->delta_x;
		game->player->pos.y += game->player->delta_y;
	}
	if (key.key == MLX_KEY_S)
	{
		game->player->pos.x -= game->player->delta_x;
		game->player->pos.y -= game->player->delta_y;
	}
	if (key.key == MLX_KEY_A)
	{
		game->player->angle -= 2;
		if (game->player->angle < 0)
			game->player->angle += (radian_to_degree(2 * M_PI));
		game->player->delta_x = cos(game->player->angle) * 5;
		game->player->delta_y = sin(game->player->angle) * 5;
	}
	if (key.key == MLX_KEY_D)
	{
		game->player->angle += 2;
		if (game->player->angle > radian_to_degree(2 * M_PI))
			game->player->angle -= radian_to_degree(2 * M_PI);
		game->player->delta_x = cos(game->player->angle) * 5;
		game->player->delta_y = sin(game->player->angle) * 5;
	}
	printf("game->player->angle = %f\n", game->player->angle);
}

void	ft_moove_player(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	color_line(game->player->img_line, ft_pixel(255, 0, 0, 0xFF), game->player);
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
		if (key.key == MLX_KEY_W || key.key == MLX_KEY_S || key.key == MLX_KEY_A
			|| key.key == MLX_KEY_D)
			ft_turn_player(key, param);
	}
}
