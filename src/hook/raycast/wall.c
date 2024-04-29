/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:44:36 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/29 22:15:28 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	r(float nb)
{
	return (int)round(nb);
}

static void	get_wall_img(t_wall *wall, t_game *game)
{
	float	player_y;
	float	player_x;
	float	fract_x;
	float	fract_y;

	player_y = game->player->img_player->instances[0].y / MAP_TILE_SIZE; // Ex 6
	player_x = game->player->img_player->instances[0].x / MAP_TILE_SIZE; // Ex 4
	fract_x = fmod(wall->collision_x, 1.0f);
	// fmod = reste après la virgule (reste de la divisione entiere de x par y)
	fract_y = fmod(wall->collision_y, 1.0f);
	if (fract_x >= 0.97 && fract_y >= 0.97)
	{
		if (!wall->img)
			wall->img = game->textures.east;
		return ;
	}
	if (player_x > wall->collision_x && fract_x >= 0.97)
		wall->img = game->textures.east;
	else if (player_x < wall->collision_x && fract_x >= 0.97)
		wall->img = game->textures.west;
	else if (player_y > wall->collision_y && fract_y >= 0.97)
		wall->img = game->textures.north;
	else if (player_y < wall->collision_y && fract_y >= 0.97)
		wall->img = game->textures.south;
	else
		printf("AUCUN CAS\n");
}

static void	compute_distance_and_select_wall(t_game *game, t_wall *wall)
{
	t_direction_line	line;
	float				theta;
	float				y;
	float				x;
	float				step_y;
	float				step_x;
	float				col_angle_rad;
	float				dist_wall;

	line.start_x = game->player->img_player->instances[0].x * TILE_FACTOR;
	// Ex 27 * 4 = 108
	line.start_y = game->player->img_player->instances[0].y * TILE_FACTOR;
	// Ex 39 * 4 = 156
	x = line.start_x; // 108
	y = line.start_y; // 156
	col_angle_rad = wall->column_angle * M_PI / 180;
	// Ex Pour col angle allant de 60 à 120 => PI/3 à 2PI/3 = 1,047197 à 2,094395
	theta = -col_angle_rad;    // Ex de -PI/3 à -2PI/3
	step_y = sin(theta) * 0.2; // Ex de 0,003655 à
								//-0,007309
	step_x = cos(theta) * 0.2;
	// Ex de 0,199966 à 0,199866
	while (true)
	{
		if (game->s_map.map[r(y) / TILE_SIZE][r(x) / TILE_SIZE] == '1')
		// Ex [r(156) / 24][r(108) / 24] = [6][4]
		{
			wall->collision_y = y / TILE_SIZE;
			wall->collision_x = x / TILE_SIZE;
			wall->distance = (sqrt(pow(x - line.start_x, 2) + pow(y
							- line.start_y, 2)));
			dist_wall = (game->player->angle * M_PI / 180) - (wall->column_angle
					* M_PI / 180);
			// Permet de faire des murs droit. (Normalisation)
			wall->height = (game->img_view_3d->height / (wall->distance
						* cos(dist_wall))) * (TILE_SIZE);
			// Ex x - line.start_x de 184,282883 - 108 à 31.715887
			//- 108 = 76.282883 à -76.284111
			// 		y - line.start_y de 23.372570 - 156 à 23.372570 - 156 =
			//		-132.627426 à -132.627426
			//    de sqrt(pow(76,282883, 2) + pow(-132,627426,
			//		2)) = sqrt(5 819,078238 + 17 590,034127) = 108,494036
			//    à  sqrt(pow(-76,284111, 2) + pow(-132,627426,
			//		2)) = sqrt(5 819,265591 + 17 590,034127) = 132,627425
			get_wall_img(wall, game);
			return ;
		}
		x += step_x;
		y += step_y;
	}
}

void	get_wall(t_game *game, t_wall *wall, float right_angle, int index)
{
	int col_nb;

	col_nb = game->img_view_3d->width;                         // Ex 645
	wall->column_angle = right_angle + (index * FOV / col_nb); // Ex 60 + (1
	//* 60
	// 645) = 60.093021
	// Puis 60 + (2 * 60 / 645) = 60.186047
	// ...
	// Jusqu'à 60 + (644 * 60 / 645) = 199,906975
	compute_distance_and_select_wall(game, wall);
}