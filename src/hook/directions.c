/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/30 21:18:30 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void rotate_right(t_game *game)
{
	game->player->angle -= ROTATE_SPEED;
	if (game->player->angle < 0)
		game->player->angle += 360;
	game->player->delta_x = cos(game->player->angle) * (ROTATE_SPEED);
	game->player->delta_y = sin(game->player->angle) * (ROTATE_SPEED);
}

static void rotate_left(t_game *game)
{
	game->player->angle += ROTATE_SPEED;
	if (game->player->angle > 360)
		game->player->angle -= 360;
	game->player->delta_x = cos(game->player->angle) * (ROTATE_SPEED);
	game->player->delta_y = sin(game->player->angle) * (ROTATE_SPEED);
}

void refresh_deltas(t_game **g)
{
	float angle_radians;
	float dx;
	float dy;

	angle_radians = (*g)->player->angle * M_PI / 180.0;
	dx = cos(-angle_radians) * (PLAYER_SPEED * 2); // dx = cos(-angle_radians) * (PLAYER_SPEED);
	dy = sin(-angle_radians) * (PLAYER_SPEED * 2); // dy = sin(-angle_radians) * (PLAYER_SPEED );
	(*g)->player->delta_x = round(dx);
	(*g)->player->delta_y = round(dy);
}

void listen_mouse_event(t_game *game)
{
	int y;
	int x;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	printf("window size: [%d] [%d] | mouse:[%d] [%d]\n", WINDOW_HEIGHT, WINDOW_WIDTH, y, x);
}

void hook_moves(void *param)
{
	t_game *game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		return (void)mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		go_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		go_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		go_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		go_right(game);
	listen_mouse_event(game);
	refresh_pixels_line(game->player->line->img_line);
	raycast(game);
}