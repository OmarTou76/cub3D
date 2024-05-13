/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:11:17 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 12:37:24 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	execute_gun_animation(t_game *game, unsigned int delay)
{
	game->animation.gun_delay++;
	if (game->animation.gun_delay >= delay)
	{
		if (game->animation.gun_frame == 1)
			break_wall(game);
		game->animation.gun_frame = (game->animation.gun_frame + 1) % 4;
		game->animation.gun_delay = 0;
		game->animation.pistol[0]->enabled = false;
		game->animation.pistol[1]->enabled = false;
		game->animation.pistol[2]->enabled = false;
		game->animation.pistol[3]->enabled = false;
		game->animation.pistol[game->animation.gun_frame]->enabled = true;
		if (game->animation.gun_frame == 0)
			game->animation.start = false;
	}
}

static int	calculate_delay(t_game *game)
{
	if (game->player->moves)
		return (2);
	else
		return (4);
}

void	shoot_animation(void *param)
{
	t_game			*game;
	unsigned int	delay;

	game = (t_game *)param;
	delay = calculate_delay(game);
	if (game->animation.start)
		execute_gun_animation(game, delay);
}

void	shoot(t_game *game)
{
	game->animation.gun_delay = 0;
	game->animation.gun_frame = 0;
	game->animation.start = true;
}
