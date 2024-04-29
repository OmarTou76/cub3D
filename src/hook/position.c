/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:23:32 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/29 11:28:26 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	update_left_and_right(mlx_key_data_t key, t_game *game, int *new_y,
		int *new_x)
{
	float	radian_angle;

	radian_angle = game->player->angle * M_PI / 180.0;
	if (key.key == MLX_KEY_A)
	{
		*new_x += (int)round(PLAYER_SPEED * cos(radian_angle + M_PI / 2.0));
		*new_y -= (int)round(PLAYER_SPEED * sin(radian_angle + M_PI / 2.0));
	}
	else if (key.key == MLX_KEY_D)
	{
		*new_x += (int)round(PLAYER_SPEED * cos(radian_angle - M_PI / 2.0));
		*new_y -= (int)round(PLAYER_SPEED * sin(radian_angle - M_PI / 2.0));
	}
}

void	update_position(mlx_key_data_t key, t_game *game, int new_y, int new_x)
{
	// delta x et y sont les vecteurs de déplacement basé sur l'orientation actuelle du joueur et la vitesse.
	if (key.key == MLX_KEY_W)
	{
		printf("I pressed W\n");
		new_x += game->player->delta_x;
		new_y += game->player->delta_y;
		printf("new_x = %d, new_y = %d IN PRESS W\n", new_x, new_y);
	}
	else if (key.key == MLX_KEY_S)
	{
		printf("I pressed S\n");
		new_x -= game->player->delta_x;
		new_y -= game->player->delta_y;
		printf("new_x = %d, new_y = %d IN PRESS S\n", new_x, new_y);
	}
	update_left_and_right(key, game, &new_y, &new_x);
	if ((game->s_map.map[new_y / MAP_TILE_SIZE][new_x / MAP_TILE_SIZE] != '1')
		&& game->s_map.map[(new_y + PLAYER_SIZE) / MAP_TILE_SIZE][(new_x
			+ PLAYER_SIZE) / MAP_TILE_SIZE] != '1')
	{
		game->player->img_player->instances[0].y = new_y;
		game->player->img_player->instances[0].x = new_x;
	}
}