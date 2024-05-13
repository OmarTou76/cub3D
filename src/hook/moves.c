/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:23:32 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 16:30:57 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_instance(mlx_instance_t *instance, int x, int y)
{
	instance->x = x;
	instance->y = y;
}

void	update_player_position(t_game *game, int new_y, int new_x)
{
	int	start_y;
	int	start_x;
	int	end_y;
	int	end_x;

	start_y = (int)((float)new_y / (float)game->map.tile_size
			- (float)game->map.padding_y / (float)game->map.tile_size);
	start_x = (int)((float)new_x / (float)game->map.tile_size
			- (float)game->map.padding_x / (float)game->map.tile_size);
	end_y = (float)(((float)new_y + (float)game->map.player_size)
			/ (float)game->map.tile_size - (float)game->map.padding_y
			/ (float)game->map.tile_size);
	end_x = (float)(((float)new_x + (float)game->map.player_size)
			/ (float)game->map.tile_size - (float)game->map.padding_x
			/ (float)game->map.tile_size);
	if (start_y == 0 || (!game->map.map[end_y + 1]
			|| end_x >= (int)ft_strlen(game->map.map[end_y + 1]))
		|| start_x == 0 || end_x >= ((int)ft_strlen(game->map.map[end_y]) - 1)
		|| game->map.map[start_y][start_x - 1] == ' ' || game->map.map[start_y
		- 1][start_x] == ' ')
		return ;
	move_instance(game->player->img_player->instances, new_x, new_y);
	game->player->moves = true;
}

static void	calcul_deltas(t_game **g)
{
	float	angle_radians;
	float	dx;
	float	dy;

	angle_radians = (*g)->player->angle * (M_PI) / 180.0;
	dx = cos(-angle_radians) * ceil((float)PLAYER_SPEED
			* ((float)(*g)->map.player_size / 10));
	dy = sin(-angle_radians) * ceil((float)PLAYER_SPEED
			* ((float)(*g)->map.player_size / 10));
	(*g)->player->delta_x = round(dx);
	(*g)->player->delta_y = round(dy);
}

void	hook_moves(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->player->moves = false;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
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
