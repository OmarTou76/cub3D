/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/12 16:07:07 by ymeziane         ###   ########.fr       */
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

int	check_wall_collision(t_game *game, int new_x, int new_y)
{
	return (game->s_map.map[new_y / TILE_SIZE][new_x / TILE_SIZE] != '1');
}

void	ft_moove_player(mlx_key_data_t key, void *param)
{
	t_game	*game;
	float	angle_radians;
	float	angle_perpendicular;
	int32_t	new_x;
	int32_t	new_y;
	int		i;

	game = (t_game *)param;
	if (key.action == MLX_PRESS || key.action == MLX_REPEAT)
	{
		if (key.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		new_x = game->player->img_player->instances[0].x;
		new_y = game->player->img_player->instances[0].y;
		angle_radians = game->player->angle * M_PI / 180.0;
		if (key.key == MLX_KEY_W)
		{
			new_x += PLAYER_SPEED * cos(angle_radians);
			new_y -= PLAYER_SPEED * sin(angle_radians);
		}
		else if (key.key == MLX_KEY_S)
		{
			new_x -= PLAYER_SPEED * cos(angle_radians);
			new_y += PLAYER_SPEED * sin(angle_radians);
		}
		else if (key.key == MLX_KEY_A)
		{
			angle_perpendicular = angle_radians + M_PI / 2.0;
			new_x += PLAYER_SPEED * cos(angle_perpendicular);
			new_y -= PLAYER_SPEED * sin(angle_perpendicular);
		}
		else if (key.key == MLX_KEY_D)
		{
			angle_perpendicular = angle_radians - M_PI / 2.0;
			new_x += PLAYER_SPEED * cos(angle_perpendicular);
			new_y -= PLAYER_SPEED * sin(angle_perpendicular);
		}
		if (check_wall_collision(game, new_x, new_y))
		{
			game->player->img_player->instances[0].x = new_x;
			game->player->img_player->instances[0].y = new_y;
		}
		color_img(game->player->line->img_line, 0,
			game->player->line->img_line->width,
			game->player->line->img_line->height);
		i = game->player->angle - 30;
		while (i < game->player->angle + 30)
		{
			color_line(game->player->line->img_line, ft_pixel(255, 0, 0, 0xFF),
				game, i);
			i += 2;
		}
		if (key.key == MLX_KEY_LEFT || key.key == MLX_KEY_RIGHT)
			ft_turn_player(key, param);
	}
}
