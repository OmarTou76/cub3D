/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:23:32 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 20:29:54 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static void	move_instance(mlx_instance_t *instance, int x, int y)
{
	instance->x = x;
	instance->y = y;
}

void	update_player_position(t_game *game, int new_y, int new_x)
{
	int	start_py;
	int	start_px;
	int	index_y;
	int	index_x;

	start_py = (int)round(((float)new_y / (float)game->map.tile_size
				- (float)game->map.padding_y / (float)game->map.tile_size));
	start_px = (int)round(((float)new_x / (float)game->map.tile_size
				- (float)game->map.padding_x / (float)game->map.tile_size));
	index_y = (int)floor(((float)new_y / (float)game->map.tile_size
				- (float)game->map.padding_y / (float)game->map.tile_size));
	index_x = (int)floor(((float)new_x / (float)game->map.tile_size
				- (float)game->map.padding_x / (float)game->map.tile_size));
	if ((game->map.map[index_y][index_x] != '1'
		&& game->map.map[index_y][index_x] != 'D')
		&& (game->map.map[(int)start_py][(int)start_px] != '1'
		&& game->map.map[(int)start_py][(int)start_px] != 'D')
		&& (game->map.map[index_y][(int)start_px] != '1'
		&& game->map.map[index_y][(int)start_px] != 'D')
		&& (game->map.map[(int)start_py][index_x] != '1'
		&& game->map.map[(int)start_py][index_x] != 'D'))
	{
		move_instance(game->player->img_player->instances, new_x, new_y);
		game->player->moves = true;
	}
}

static void	calcul_deltas(t_game **g)
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
