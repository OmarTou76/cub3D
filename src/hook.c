/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/12 13:11:48 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	refresh_deltas(t_game **g)
{
	float	angle_radians;
	int		distance;
	int		dx;
	int		dy;
	t_game	*game;

	game = (*g);
	game->player->delta_x = cos(game->player->angle) * 5;
	game->player->delta_y = sin(game->player->angle) * 5;
	angle_radians = game->player->angle * M_PI / 180.0;
	distance = 5;
	dx = distance * cos(-angle_radians);
	dy = distance * sin(-angle_radians);
	(*g)->player->delta_x = dx;
	(*g)->player->delta_y = dy;
}

static void	ft_turn_player(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	refresh_deltas(&game);
	if (key.key == MLX_KEY_RIGHT)
	{
		game->player->angle -= 5;
		if (game->player->angle < 0)
			game->player->angle += (radian_to_degree(2 * M_PI));
		game->player->delta_x = cos(game->player->angle) * 5;
		game->player->delta_y = sin(game->player->angle) * 5;
	}
	if (key.key == MLX_KEY_LEFT)
	{
		game->player->angle += 5;
		if (game->player->angle > radian_to_degree(2 * M_PI))
			game->player->angle -= radian_to_degree(2 * M_PI);
		game->player->delta_x = cos(game->player->angle) * 5;
		game->player->delta_y = sin(game->player->angle) * 5;
	}
}

void	ft_moove_player(mlx_key_data_t key, void *param)
{
	t_game	*game;
	float	angle_radians;
	float	angle_perpendicular;

	game = (t_game *)param;
	if (key.action == MLX_PRESS || key.action == MLX_REPEAT)
	{
		if (key.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		angle_radians = game->player->angle * M_PI / 180.0;
		if (key.key == MLX_KEY_W)
		{
			game->player->img_player->instances[0].x += PLAYER_SPEED
				* cos(angle_radians);
			game->player->img_player->instances[0].y -= PLAYER_SPEED
				* sin(angle_radians);
		}
		else if (key.key == MLX_KEY_S)
		{
			game->player->img_player->instances[0].x -= PLAYER_SPEED
				* cos(angle_radians);
			game->player->img_player->instances[0].y += PLAYER_SPEED
				* sin(angle_radians);
		}
		else if (key.key == MLX_KEY_A)
		{
			// Déplacement vers la gauche (perpendiculaire à la direction du joueur)
			angle_perpendicular = angle_radians + M_PI / 2.0;
			// Ajoute 90 degrés
			game->player->img_player->instances[0].x += PLAYER_SPEED
				* cos(angle_perpendicular);
			game->player->img_player->instances[0].y -= PLAYER_SPEED
				* sin(angle_perpendicular);
		}
		else if (key.key == MLX_KEY_D)
		{
			// Déplacement vers la droite (perpendiculaire à la direction du joueur)
			angle_perpendicular = angle_radians - M_PI / 2.0;
			// Soustrait 90 degrés
			game->player->img_player->instances[0].x += PLAYER_SPEED
				* cos(angle_perpendicular);
			game->player->img_player->instances[0].y -= PLAYER_SPEED
				* sin(angle_perpendicular);
		}
		color_img(game->player->img_line, 0, game->player->img_line->width,
			game->player->img_line->height);
		for (double i = game->player->angle - 30; i < game->player->angle
			+ 30; i += 2)
			color_line(game->player->img_line, ft_pixel(255, 0, 0, 0xFF), game,
				i);
		if (key.key == MLX_KEY_LEFT || key.key == MLX_KEY_RIGHT)
			ft_turn_player(key, param);
	}
}
