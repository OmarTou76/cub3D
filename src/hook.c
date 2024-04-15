/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/15 10:49:28 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	refresh_deltas(t_game **g)
{
	float	angle_radians;
	int		dx;
	int		dy;

	angle_radians = (*g)->player->angle * M_PI / 180.0;
	dx = PLAYER_SPEED * cos(-angle_radians);
	dy = PLAYER_SPEED * sin(-angle_radians);
	(*g)->player->delta_x = dx;
	(*g)->player->delta_y = dy;
}

static void	update_left_and_right(mlx_key_data_t key, t_game *game, int *new_y,
		int *new_x)
{
	if (key.key == MLX_KEY_A)
	{
		*new_x += PLAYER_SPEED * cos((game->player->angle * M_PI / 180.0) + M_PI
				/ 2.0);
		*new_y -= PLAYER_SPEED * sin((game->player->angle * M_PI / 180.0) + M_PI
				/ 2.0);
	}
	else if (key.key == MLX_KEY_D)
	{
		*new_x += PLAYER_SPEED * cos((game->player->angle * M_PI / 180.0) - M_PI
				/ 2.0);
		*new_y -= PLAYER_SPEED * sin((game->player->angle * M_PI / 180.0) - M_PI
				/ 2.0);
	}
}

static void	check_and_moves(mlx_key_data_t key, t_game *game, int new_y,
		int new_x)
{
	if (key.key == MLX_KEY_W)
	{
		new_x += game->player->delta_x;
		new_y += game->player->delta_y;
	}
	else if (key.key == MLX_KEY_S)
	{
		new_x -= game->player->delta_x;
		new_y -= game->player->delta_y;
	}
	update_left_and_right(key, game, &new_y, &new_x);
	if ((game->s_map.map[new_y / TILE_SIZE][new_x / TILE_SIZE] != '1')
		&& game->s_map.map[(new_y + PLAYER_SIZE) / TILE_SIZE][(new_x
			+ PLAYER_SIZE) / TILE_SIZE] != '1')
	{
		game->player->img_player->instances[0].y = new_y;
		game->player->img_player->instances[0].x = new_x;
	}
}

static void	ft_turn_player(mlx_key_data_t key, t_game *game)
{
	refresh_deltas(&game);
	if (key.key == MLX_KEY_RIGHT)
	{
		game->player->angle -= 5;
		if (game->player->angle < 0)
			game->player->angle += (radian_to_degree(2 * M_PI));
		game->player->delta_x = cos(game->player->angle) * 5;
		game->player->delta_y = sin(game->player->angle) * 5;
	}
	else if (key.key == MLX_KEY_LEFT)
	{
		game->player->angle += 5;
		if (game->player->angle > radian_to_degree(2 * M_PI))
			game->player->angle -= radian_to_degree(2 * M_PI);
		game->player->delta_x = cos(game->player->angle) * 5;
		game->player->delta_y = sin(game->player->angle) * 5;
	}
	else
		check_and_moves(key, game, game->player->img_player->instances[0].y,
			game->player->img_player->instances[0].x);
}

void	ft_moove_player(mlx_key_data_t key, void *param)
{
	t_game	*game;
	int		i;

	game = (t_game *)param;
	if (key.action == MLX_PRESS || key.action == MLX_REPEAT)
	{
		if (key.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (key.key == MLX_KEY_W || key.key == MLX_KEY_S
			|| key.key == MLX_KEY_A || key.key == MLX_KEY_D
			|| key.key == MLX_KEY_LEFT || key.key == MLX_KEY_RIGHT)
			ft_turn_player(key, param);
		color_img(game->player->line->img_line, 0,
			game->player->line->img_line->width,
			game->player->line->img_line->height);
		color_img(game->img_view_3d, 0, game->img_view_3d->width,
			game->img_view_3d->height);
		i = game->player->angle - 30;
		while (i < game->player->angle + 30)
		{
			color_line(game->player->line->img_line, ft_pixel(255, 0, 0, 0xFF),
				game, i);
			i++;
		}
	}
}
