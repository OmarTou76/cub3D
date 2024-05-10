/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:44:36 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/11 00:39:30 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_border_wall_index(t_wall *wall, float player_y, float player_x)
{
	if (player_y >= roundf(wall->collision_y) && player_x > wall->collision_x)
		return (0);
	else if (player_y < wall->collision_y && player_x > wall->collision_x)
		return (2);
	else if (player_y > wall->collision_y && player_x < wall->collision_x)
		return (3);
	else if (player_y < wall->collision_y && player_x < wall->collision_x)
		return (1);
	return (-1);
}

static int	get_wall_index(t_wall *wall, t_game *game)
{
	int		texture_index;
	float	player_y;
	float	player_x;
	float	fract_x;
	float	fract_y;

	texture_index = -1;
	player_y = ((float)game->player->img_player->instances[0].y
			+ (float)game->player->img_player->height / 2)
		/ (float)game->map.tile_size - (float)game->map.padding_y
		/ (float)game->map.tile_size;
	player_x = (float)(game->player->img_player->instances[0].x
			+ (float)game->player->img_player->width / 2)
		/ (float)game->map.tile_size - (float)game->map.padding_x
		/ (float)game->map.tile_size;
	fract_x = fmodf(wall->collision_x, 1.0f);
	fract_y = fmodf(wall->collision_y, 1.0f);
	if (((fract_y >= 0.99 && fract_x < 0.99) && (fract_x <= 0.01
				&& fract_y > 0.01)) || ((fract_y <= 0.01 && fract_x > 0.01)
			&& (fract_x >= 0.99 && fract_y < 0.99)) || (fract_x >= 0.99
			&& fract_y >= 0.99) || (fract_y <= 0.01 && fract_x <= 0.01))
	{
		if (fabs(wall->collision_y - wall->last_collision_y) > 0.1)
			texture_index = get_border_wall_index(wall, player_y, player_x);
	}
	else if (player_y > wall->collision_y && (fract_y >= 0.99
			&& fract_x < 0.99))
		texture_index = 0;
	else if (player_x < wall->collision_x && (fract_x <= 0.01
			&& fract_y > 0.01))
		texture_index = 3;
	else if (player_y < wall->collision_y && (fract_y <= 0.01
			&& fract_x > 0.01))
		texture_index = 1;
	else if (player_x > wall->collision_x && (fract_x >= 0.99
			&& fract_y < 0.99))
		texture_index = 2;
	return (texture_index);
}

static void	get_wall_img(t_wall *wall, t_game *game)
{
	int	texture_index;

	texture_index = get_wall_index(wall, game);
	if (texture_index == 0)
		wall->img = game->textures.north;
	else if (texture_index == 1)
		wall->img = game->textures.south;
	else if (texture_index == 2)
		wall->img = game->textures.west;
	else if (texture_index == 3)
		wall->img = game->textures.east;
	else if (texture_index == -1 && !wall->img)
		wall->img = game->textures.north; // Par defaut
	wall->crack = is_cracked_wall(wall, game, texture_index);
	wall->last_collision_x = wall->collision_x;
	wall->last_collision_y = wall->collision_y;
}

void	compute_distance_and_select_wall(t_game *game, t_wall *wall)
{
	t_ray_direction	ray;

	init_ray_properties(&ray, game, wall);
	while (true)
	{
		wall->collision_y = (ray.end_y / (float)game->map.tile_size
				- (float)game->map.padding_y / (float)game->map.tile_size);
		wall->collision_x = (ray.end_x / (float)game->map.tile_size
				- (float)game->map.padding_x / (float)game->map.tile_size);
		if (game->map.map[(int)wall->collision_y][(int)wall->collision_x] == '1'
			|| game->map.map[(int)wall->collision_y][(int)wall->collision_x] == 'D')
		{
			wall->distance = (sqrt(pow(ray.end_x - ray.start_x, 2)
						+ pow(ray.end_y - ray.start_y, 2)));
			ray.final_collision_dist = (game->player->angle * M_PI / 180)
				- (wall->column_angle * M_PI / 180);
			wall->height = (game->img_view_3d->height / (wall->distance
						* cos(ray.final_collision_dist)))
				* (game->map.tile_size);
			return (get_wall_img(wall, game));
		}
		mlx_put_pixel(game->map.rays.img_line, ray.end_x, ray.end_y,
			ft_pixel(245, 40, 100, 0xFF));
		ray.end_x += ray.step_x;
		ray.end_y += ray.step_y;
	}
}

void	get_wall(t_game *game, t_wall *wall, float right_angle, int index)
{
	int	col_nb;

	col_nb = game->img_view_3d->width;
	wall->crack = false;
	wall->column_angle = right_angle + (index * FOV / col_nb);
	compute_distance_and_select_wall(game, wall);
}
