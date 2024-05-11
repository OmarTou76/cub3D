/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/11 13:07:26 by ymeziane         ###   ########.fr       */
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
	game->player->moves = true;
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
	game->player->moves = true;
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

void	get_collision_point(t_vec *door, t_wall target, t_game *game)
{
	int		player_x;
	int		player_y;
	float	fract_x;
	float	fract_y;

	player_y = game->player->img_player->instances[0].y / game->map.tile_size
		- game->map.padding_y / game->map.tile_size;
	player_x = game->player->img_player->instances[0].x / game->map.tile_size
		- game->map.padding_x / game->map.tile_size;
	fract_x = fmod(target.collision_x, 1.0f);
	fract_y = fmod(target.collision_y, 1.0f);
	if (game->map.map[(int)(target.collision_y)][(int)(target.collision_x)] == 'D')
	{
		door->y = (int)(target.collision_y);
		door->x = (int)(target.collision_x);
	}
	else if (player_x < target.collision_x && fract_x >= 0.97
		&& game->map.map[(int)(target.collision_y)][(int)ceil(target.collision_x)] == 'D')
	{
		door->y = (int)(target.collision_y);
		door->x = (int)ceil(target.collision_x);
	}
	else if (player_y < target.collision_y && fract_y >= 0.97
		&& game->map.map[(int)ceil(target.collision_y)][(int)(target.collision_x)] == 'D')
	{
		door->y = (int)ceil(target.collision_y);
		door->x = (int)(target.collision_x);
	}
}

void	break_wall(t_game *game)
{
	t_wall	target;
	t_vec	collision;

	target.crack = false;
	target.column_angle = game->player->angle;
	compute_distance_and_select_wall(game, &target);
	if (target.crack)
	{
		get_collision_point(&collision, target, game);
		game->map.map[collision.y][collision.x] = '0';
		fill_by_pixel(game->map, (collision.y * game->map.tile_size),
			(collision.x * game->map.tile_size), ft_pixel(150, 150, 150, 0x90));
		raycast(game);
	}
	// write(1, "\a", 1); // "Bruit de l'arme"
}

void	shoot_animation(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	unsigned int delay;

	if(game->player->moves)
		delay = 1;
	else
		delay = 10;
	if (game->animation.start)
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
}

void	shoot(t_game *game)
{
	game->animation.gun_delay = 0;
	game->animation.gun_frame = 0;
	game->animation.start = true;
}

void	hook_moves(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->player->moves = false;
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
