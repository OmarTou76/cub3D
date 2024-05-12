/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 13:12:42 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	rotate_right(t_game *game, bool is_mouse_event)
{
	int	rotate;

	if (is_mouse_event)
		rotate = (ROTATE_SPEED / 2);
	else
		rotate = ROTATE_SPEED;
	game->player->angle -= rotate;
	if (game->player->angle < 0)
		game->player->angle += 360;
	game->player->moves = true;
}

static void	rotate_left(t_game *game, bool is_mouse_event)
{
	int	rotate;

	if (is_mouse_event)
		rotate = (ROTATE_SPEED / 2);
	else
		rotate = ROTATE_SPEED;
	game->player->angle += rotate;
	if (game->player->angle > 360)
		game->player->angle -= 360;
	game->player->moves = true;
}

void	calcul_deltas(t_game **g)
{
	float	angle_radians;
	float	dx;
	float	dy;

	angle_radians = (*g)->player->angle * (M_PI) / 180.0;
	dx = cos(-angle_radians) * (PLAYER_SPEED);
	dy = sin(-angle_radians) * (PLAYER_SPEED);
	(*g)->player->delta_x = round(dx);
	(*g)->player->delta_y = round(dy);
}

void	listen_mouse_event(t_game *game)
{
	int	y;
	int	x;

	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x < (WINDOW_WIDTH / 2) && x > 0 && y > 0 && y < WINDOW_HEIGHT)
		rotate_left(game, true);
	else if (x > (WINDOW_WIDTH / 2) && x < WINDOW_WIDTH && y > 0
		&& y < WINDOW_HEIGHT)
		rotate_right(game, true);
	if (x < WINDOW_WIDTH / 2 || x > WINDOW_WIDTH / 2)
		mlx_set_mouse_pos(game->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void	hook_moves(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->player->moves = false;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game, false);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game, false);
	calcul_deltas(&game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		go_forward(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		go_backward(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		go_left(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		go_right(game);
}
