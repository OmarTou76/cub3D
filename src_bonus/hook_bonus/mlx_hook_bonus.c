/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:17:10 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 14:35:39 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_hook(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if ((key.action == MLX_PRESS) && key.key == MLX_KEY_M)
		display_map(game);
	if ((key.action == MLX_PRESS) && (key.key == MLX_KEY_LEFT_CONTROL
			|| key.key == MLX_KEY_RIGHT_CONTROL))
	{
		if (game->mouse_event == true)
		{
			game->mouse_event = false;
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
		}
		else
		{
			game->mouse_event = true;
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
		}
	}
}

void	loop_hook(void *param)
{
	t_game	*game;
	int		prev_x;
	int		prev_y;
	float	prev_angle;

	game = (t_game *)param;
	prev_x = game->player->img_player->instances[0].x;
	prev_y = game->player->img_player->instances[0].y;
	prev_angle = game->player->angle;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		return ((void)mlx_close_window(game->mlx));
	if (!game->animation.start && (mlx_is_mouse_down(game->mlx,
				MLX_MOUSE_BUTTON_LEFT) || mlx_is_key_down(game->mlx,
				MLX_KEY_F)))
		shoot(game);
	listen_mouse_event(game);
	shoot_animation(game);
	hook_moves(game);
	if (prev_x == game->player->img_player->instances[0].x
		&& game->player->img_player->instances[0].y == prev_y
		&& game->player->angle == prev_angle)
		return ;
	refresh_pixels_line(game->map.rays.img_line);
	raycast(game);
}
