/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otourabi <otourabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/06 18:05:03 by otourabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	rotate_right(t_game *game, bool is_mouse_event)
{
	int	rotate;

	if (is_mouse_event)
		rotate = (ROTATE_SPEED / 2);
	else
		rotate = ROTATE_SPEED;
	game->player->angle -= rotate;
	if (game->player->angle < 0)
		game->player->angle += 360;
}

static void	rotate_left(t_game *game, bool is_mouse_event)
{
	int	rotate;

	if (is_mouse_event)
		rotate = (ROTATE_SPEED / 2);
	else
		rotate = ROTATE_SPEED;
	game->player->angle += rotate;
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
	int	y;
	int	x;

	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x < (WINDOW_WIDTH / 2) && x > 0 && y > 0 && y < WINDOW_HEIGHT)
		rotate_left(game, true);
	else if (x > (WINDOW_WIDTH / 2) && x < WINDOW_WIDTH && y > 0
		&& y < WINDOW_HEIGHT)
		rotate_right(game, true);
	if (x < WINDOW_WIDTH / 2 || x > WINDOW_WIDTH / 2)
		mlx_set_mouse_pos(game->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void	break_wall(t_game *game)
{
	t_wall	target;
	int		y;
	int		x;
	int		paddingY;
	int		paddingX;
	int		player_x;
	int		player_y;

	paddingY = (WINDOW_HEIGHT - game->s_map.img_map->height) / 2;
	paddingX = (WINDOW_WIDTH - game->s_map.img_map->width) / 2;
	target.column_angle = game->player->angle;
	player_y = game->player->img_player->instances[0].y / game->s_map.tile_size
		- paddingY / game->s_map.tile_size;
	player_x = game->player->img_player->instances[0].x / game->s_map.tile_size
		- paddingX / game->s_map.tile_size;
	compute_distance_and_select_wall(game, &target, false);
	float fract_x = fmod(target.collision_x, 1.0f);
	float fract_y = fmod(target.collision_y, 1.0f);
	y = (int)(target.collision_y);
	x = (int)(target.collision_x);
	if (game->s_map.map[(int)(target.collision_y)][(int)(target.collision_x)] == 'D')
	{
		game->s_map.map[(int)(target.collision_y)][(int)(target.collision_x)] = '0';
		fill_by_pixel(game->s_map, (y * game->s_map.tile_size), (x
				* game->s_map.tile_size), ft_pixel(150, 150, 150, 0x90));
		raycast(game);
	}
	else if (player_x < target.collision_x && fract_x >= 0.97 && game->s_map.map[(int)(target.collision_y)][(int)ceil(target.collision_x)] == 'D')
	{
		game->s_map.map[(int)(target.collision_y)][(int)ceil(target.collision_x)] = '0';
		fill_by_pixel(game->s_map, (y * game->s_map.tile_size), (x
				* game->s_map.tile_size), ft_pixel(150, 150, 150, 0x90));
		raycast(game);
	}
	else if (player_y < target.collision_y && fract_y >= 0.97 && game->s_map.map[(int)ceil(target.collision_y)][(int)(target.collision_x)] == 'D')
	{
		game->s_map.map[(int)ceil(target.collision_y)][(int)(target.collision_x)] = '0';
		fill_by_pixel(game->s_map, (y * game->s_map.tile_size), (x
				* game->s_map.tile_size), ft_pixel(150, 150, 150, 0x90));
		raycast(game);
	}
	write(1, "\a",1);
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
			if (game->gun_frame == 1)
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

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game, false);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game, false);
	calcul_deltas(&game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		go_forward(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		go_backward(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		go_left(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		go_right(game);
}
