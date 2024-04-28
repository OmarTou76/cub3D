/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/28 13:33:24 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	refresh_deltas(t_game **g)
{
	float	angle_radians;
	float	dx;
	float	dy;

	angle_radians = (*g)->player->angle * M_PI / 180.0; // Ex 90 => Pi / 2
	dx = PLAYER_SPEED * cos(-angle_radians);
	// Ex (MAP_TILE_SIZE) / 5 * cos(-PI/2) = (TILE_SIZE / TILE_FACTOR) / 5 * cos(-PI/2) = (24 / 4) / 5 * cos(-PI/2) = 1 * cos(-PI/2) = 0
	dy = PLAYER_SPEED * sin(-angle_radians);
	// Ex (24 / 4) / 5 * sin(-PI/2) = 1 * sin(-PI/2) = -1
	(*g)->player->delta_x = round(dx); // distance que le joueur doit se déplacer horizontalement Ex 0
	(*g)->player->delta_y = round(dy); // distance que le joueur doit se déplacer verticalement Ex -1
}

void	handle_moves(mlx_key_data_t key, t_game *game)
{
	refresh_deltas(&game);
	if (key.key == MLX_KEY_RIGHT)
	{
		game->player->angle -= ROTATE_SPEED; // Ex -= 3
		if (game->player->angle < 0)
			game->player->angle += 360;
		game->player->delta_x = cos(game->player->angle) * (ROTATE_SPEED); // Ex dx passe de 0 à 3.000000 si je tourne jusqu' angle = 0(ou 360) car cos(0) = 1 et ROTATE_SPEED = 3
		game->player->delta_y = sin(game->player->angle) * (ROTATE_SPEED); // Ex dx passe de -1 à 0 si je tourne jusqu' angle = 0(ou 360) car sin(0) = 0
	}
	else if (key.key == MLX_KEY_LEFT) // Pareil de l'autre côté
	{
		game->player->angle += ROTATE_SPEED;
		if (game->player->angle > 360)
			game->player->angle -= 360;
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
