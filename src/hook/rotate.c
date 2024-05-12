/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 19:29:02 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_right(t_game *game, bool is_mouse_event)
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

void	rotate_left(t_game *game, bool is_mouse_event)
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
