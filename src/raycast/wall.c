/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:44:36 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/09 04:04:16 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int r(float nb)
{
	return (int)round(nb);
}

static void get_wall_img(t_wall *wall, t_game *game)
{
	int paddingY;
	int paddingX;

	paddingY = (WINDOW_HEIGHT - game->s_map.img_map->height) / 2;
	paddingX = (WINDOW_WIDTH - game->s_map.img_map->width) / 2;
	float player_y = game->player->img_player->instances[0].y / game->s_map.tile_size - paddingY / game->s_map.tile_size;
	float player_x = game->player->img_player->instances[0].x / game->s_map.tile_size - paddingX / game->s_map.tile_size;
	float fract_x = fmodf(wall->collision_x, 1.0f);
	float fract_y = fmodf(wall->collision_y, 1.0f);
	float dist_wall_max = 0.2;
	int texture_index = -1;

	if (fract_x >= 0.97 && fract_y >= 0.97)
	{
		if (player_y < wall->collision_y && player_x < wall->collision_x && fabs(wall->collision_y - wall->last_collision_y) >= dist_wall_max)
			texture_index = 1;
		else if (player_y < wall->collision_y && player_x > wall->collision_x && fabs(wall->collision_y - wall->last_collision_y) >= dist_wall_max)
			texture_index = 3;
		else if (player_y > wall->collision_y && player_x > wall->collision_x && fabs(wall->collision_y - wall->last_collision_y) >= dist_wall_max)
			texture_index = 0;
		else if (player_y > wall->collision_y && player_x < wall->collision_x && fabs(wall->collision_y - wall->last_collision_y) >= dist_wall_max)
			texture_index = 2;
	}
	else if (player_x > wall->collision_x && fract_x >= 0.97)
		texture_index = 3;
	else if (player_y > wall->collision_y && fract_y >= 0.97)
		texture_index = 0;
	else if (player_x < wall->collision_x && fract_x >= 0.97)
		texture_index = 2;
	else if (player_y < wall->collision_y && fract_y >= 0.97)
		texture_index = 1;
	if (texture_index == 0)
	{
		if (game->s_map.map[(int)(wall->collision_y)][(int)(wall->collision_x)] == 'D')
			wall->crack = true;
		wall->img = game->textures.north;
	}
	else if (texture_index == 1)
	{
		if (game->s_map.map[(int)ceil(wall->collision_y)][(int)(wall->collision_x)] == 'D')
			wall->crack = true;
		wall->img = game->textures.south;
	}
	else if (texture_index == 2)
	{
		if (game->s_map.map[(int)(wall->collision_y)][(int)ceil(wall->collision_x)] == 'D')
			wall->crack = true;
		wall->img = game->textures.west;
	}
	else if (texture_index == 3)
	{
		if (game->s_map.map[(int)(wall->collision_y)][(int)(wall->collision_x)] == 'D')
			wall->crack = true;
		wall->img = game->textures.east;
	}
	else if (texture_index == -1 && !wall->img)
		wall->img = game->textures.north; // Par defaut
	wall->last_collision_x = wall->collision_x;
	wall->last_collision_y = wall->collision_y;
}

void compute_distance_and_select_wall(t_game *game, t_wall *wall,
									  bool center_texture)
{
	t_direction_line line;
	float theta;
	float y;
	float x;
	float step_y;
	float step_x;
	float col_angle_rad;
	float dist_wall;
	int paddingY;
	int paddingX;

	paddingY = (WINDOW_HEIGHT - game->s_map.img_map->height) / 2;
	paddingX = (WINDOW_WIDTH - game->s_map.img_map->width) / 2;
	line.start_x = game->player->img_player->instances[0].x;
	line.start_y = game->player->img_player->instances[0].y;
	x = line.start_x;
	y = line.start_y;
	col_angle_rad = wall->column_angle * M_PI / 180;
	theta = -col_angle_rad;
	step_y = sin(theta) * 0.2;
	step_x = cos(theta) * 0.2;
	(void)center_texture;
	while (true)
	{
		if ((game->s_map.map[r(y) / game->s_map.tile_size - paddingY / game->s_map.tile_size][r(x) / game->s_map.tile_size - paddingX / game->s_map.tile_size] == '1') || (game->s_map.map[r(y) / game->s_map.tile_size - paddingY / game->s_map.tile_size][r(x) / game->s_map.tile_size - paddingX / game->s_map.tile_size] == 'D'))
		{
			wall->collision_y = y / game->s_map.tile_size - paddingY / game->s_map.tile_size;
			wall->collision_x = x / game->s_map.tile_size - paddingX / game->s_map.tile_size;
			wall->distance = (sqrt(pow(x - line.start_x, 2) + pow(y - line.start_y, 2)));
			dist_wall = (game->player->angle * M_PI / 180) - (wall->column_angle * M_PI / 180);
			wall->height = (game->img_view_3d->height / (wall->distance * cos(dist_wall))) * (game->s_map.tile_size);
			get_wall_img(wall, game);
			return;
		}
		x += step_x;
		y += step_y;
	}
}

void get_wall(t_game *game, t_wall *wall, float right_angle, int index)
{
	int col_nb;
	bool center_texture;

	col_nb = game->img_view_3d->width;
	wall->column_angle = right_angle + (index * FOV / col_nb);
	if (index == col_nb / 2)
		center_texture = true;
	else
		center_texture = false;
	compute_distance_and_select_wall(game, wall, center_texture);
}