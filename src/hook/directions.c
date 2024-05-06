/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/06 04:54:17 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	rotate_right(t_game *game)
{
	game->player->angle -= ROTATE_SPEED;
	if (game->player->angle < 0)
		game->player->angle += 360;
}

static void	rotate_left(t_game *game)
{
	game->player->angle += ROTATE_SPEED;
	if (game->player->angle > 360)
		game->player->angle -= 360;
}

void	calcul_deltas(t_game **g)
{
	float	angle_radians;
	float	dx;
	float	dy;

	angle_radians = (*g)->player->angle * (M_PI) / 180.0;
	dx = cos(-angle_radians) * (PLAYER_SPEED);
	dy = sin(-angle_radians) * (PLAYER_SPEED);
	(*g)->player->delta_x = round(dx);
	(*g)->player->delta_y = round(dy);
}

void	listen_mouse_event(t_game *game)
{
	// int	y;

	/* int x;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x < (WINDOW_WIDTH / 2) && x > 0 && y > 0 && y < WINDOW_HEIGHT)
		rotate_left(game);
	else if (x > (WINDOW_WIDTH / 2) && x < WINDOW_WIDTH && y > 0
		&& y < WINDOW_HEIGHT)
		rotate_right(game);
	if (x < WINDOW_WIDTH / 2 || x > WINDOW_WIDTH / 2)
		mlx_set_mouse_pos(game->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); */
	(void)game;
}

void	break_wall(t_game *game)
{
	int	x;
	int	y;

	x = game->textures.center_texture.x;
	y = game->textures.center_texture.y;
	if(game->s_map.map[y][x] == 'D')
	{
		game->s_map.map[y][x] = '0';
		fill_by_pixel(game->s_map, (y * game->s_map.tile_size), (x * game->s_map.tile_size), ft_pixel(150, 150, 150, 0x90));
		raycast(game);
	}
}

void	shoot_animation(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->shoot)
	{
		game->gun_delay++;
		if (game->gun_delay >= 5)
		{
			if(game->gun_frame == 1)
				break_wall(game);
			game->gun_frame = (game->gun_frame + 1) % 4;
			game->gun_delay = 0;
			game->textures.pistol[0]->enabled = false;
			game->textures.pistol[1]->enabled = false;
			game->textures.pistol[2]->enabled = false;
			game->textures.pistol[3]->enabled = false;
			game->textures.pistol[game->gun_frame]->enabled = true;
			if (game->gun_frame == 0)
				game->shoot = false;
		}
	}
}

void	shoot(t_game *game)
{
	game->gun_delay = 0;
	game->gun_frame = 0;
	game->shoot = true;
}

void	hook_moves(void *param)
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
		return (void)mlx_close_window(game->mlx);
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
	if (prev_x == game->player->img_player->instances[0].x
		&& game->player->img_player->instances[0].y == prev_y
		&& game->player->angle == prev_angle)
		return ;
	refresh_pixels_line(game->player->line->img_line);
	raycast(game);
}
