/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/26 19:12:27 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	refresh_deltas(t_game **g)
{
	float	angle_radians;
	float	dx;
	float	dy;

	angle_radians = (*g)->player->angle * M_PI / 180.0;
	dx = PLAYER_SPEED * cos(-angle_radians);
	dy = PLAYER_SPEED * sin(-angle_radians);
	(*g)->player->delta_x = round(dx);
	(*g)->player->delta_y = round(dy);
}

void	handle_moves(mlx_key_data_t key, t_game *game)
{
	refresh_deltas(&game);
	if (key.key == MLX_KEY_RIGHT)
	{
		game->player->angle -= ROTATE_SPEED;
		if (game->player->angle < 0)
			game->player->angle += (radian_to_degree(2 * M_PI));
		game->player->delta_x = cos(game->player->angle) * (ROTATE_SPEED);
		game->player->delta_y = sin(game->player->angle) * (ROTATE_SPEED);
	}
	else if (key.key == MLX_KEY_LEFT)
	{
		game->player->angle += ROTATE_SPEED;
		if (game->player->angle > radian_to_degree(2 * M_PI))
			game->player->angle -= radian_to_degree(2 * M_PI);
		game->player->delta_x = cos(game->player->angle) * (ROTATE_SPEED);
		game->player->delta_y = sin(game->player->angle) * (ROTATE_SPEED);
	}
	else
		update_position(key, game, game->player->img_player->instances[0].y,
			game->player->img_player->instances[0].x);
}

void	ft_move_player(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key.action == MLX_PRESS || key.action == MLX_REPEAT)
	{
		if (key.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (key.key == MLX_KEY_H)
			handle_map_display(game);
		else if (key.key == MLX_KEY_W || key.key == MLX_KEY_S
			|| key.key == MLX_KEY_A || key.key == MLX_KEY_D
			|| key.key == MLX_KEY_LEFT || key.key == MLX_KEY_RIGHT)
			handle_moves(key, param);
		refresh_pixels_line(game->player->line->img_line);
		raycast(game);
	}
}
