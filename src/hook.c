/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/10 11:05:43 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	refresh_deltas(t_game **g)
{
	float	angle_radians;
	int		distance;
	int		dx;
	int		dy;
	t_game	*game;

	game = (*g);
	game->player->delta_x = cos(game->player->angle) * 5;
	game->player->delta_y = sin(game->player->angle) * 5;
	angle_radians = game->player->angle * M_PI / 180.0;
	distance = 5;
	dx = distance * cos(-angle_radians);
	dy = distance * sin(-angle_radians);
	(*g)->player->delta_x = dx;
	(*g)->player->delta_y = dy;
}

static void	ft_turn_player(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	refresh_deltas(&game);
	if (key.key == MLX_KEY_RIGHT)
	{
		game->player->angle -= 5;
		if (game->player->angle < 0)
			game->player->angle += (radian_to_degree(2 * M_PI));
		game->player->delta_x = cos(game->player->angle) * 5;
		game->player->delta_y = sin(game->player->angle) * 5;
	}
	if (key.key == MLX_KEY_LEFT)
	{
		game->player->angle += 5;
		if (game->player->angle > radian_to_degree(2 * M_PI))
			game->player->angle -= radian_to_degree(2 * M_PI);
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
		if (key.key == MLX_KEY_W)
			game->player->img_player->instances[0].y -= TILE_SIZE / 5;
		if (key.key == MLX_KEY_S)
			game->player->img_player->instances[0].y += TILE_SIZE / 5;
		if (key.key == MLX_KEY_A)
			game->player->img_player->instances[0].x -= TILE_SIZE / 5;
		if (key.key == MLX_KEY_D)
			game->player->img_player->instances[0].x += TILE_SIZE / 5;
		color_line(game->player->img_line, ft_pixel(255, 0, 0, 0xFF), game->player);
		if (key.key == MLX_KEY_LEFT || key.key == MLX_KEY_RIGHT)
			ft_turn_player(key, param);
	}
}
