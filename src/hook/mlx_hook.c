/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:17:10 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 14:41:41 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		return (mlx_close_window(game->mlx));
	hook_moves(game);
	if (prev_x == game->player->img_player->instances[0].x
		&& game->player->img_player->instances[0].y == prev_y
		&& game->player->angle == prev_angle)
		return ;
	raycast(game);
}
