/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otourabi <otourabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:53:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/18 17:11:19 by otourabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_and_draw_player(t_game *game)
{
	uint32_t	color;

	color = ft_pixel(0, 255, 0, 0xFF);
	game->player->img_player = mlx_new_image(game->mlx, PLAYER_SIZE,
			PLAYER_SIZE);
	if (!game->player->img_player || (mlx_image_to_window(game->mlx,
				game->player->img_player, game->player->pos.x * MAP_TILE_SIZE
				+ MAP_TILE_SIZE / 2 - PLAYER_SIZE / 2, game->player->pos.y
				* MAP_TILE_SIZE + MAP_TILE_SIZE / 2 - PLAYER_SIZE / 2) == -1))
		return (printf("Error\n"), (void)NULL);
	color_img(game->player->img_player, color, PLAYER_SIZE, PLAYER_SIZE);
	game->player->img_player->instances[0].z = 3;
	game->player->img_player->instances[0].enabled = false;
}

void	initialize_line_data(t_direction_line *line, double angle,
		t_game *game)
{
	float	angle_radians;

	line->start_x = game->player->line->length;
	line->start_y = game->player->line->length;
	angle_radians = angle * M_PI / 180.0;
	line->end_x = line->start_x + game->player->line->length * cos(angle_radians);
	line->end_y = line->start_y - game->player->line->length * sin(angle_radians);
	line->delta_x = abs(line->end_x - line->start_x);
	line->delta_y = abs(line->end_y - line->start_y);
	if (line->start_x < line->end_x)
		line->step_x = 1;
	else
		line->step_x = -1;
	if (line->start_y < line->end_y)
		line->step_y = 1;
	else
		line->step_y = -1;
	line->error = line->delta_x - line->delta_y;
}

uint32_t	convert_rgba_to_argb(uint32_t rgba)
{
	uint8_t red = (rgba >> 24) & 0xFF;   // Extract red
	uint8_t green = (rgba >> 16) & 0xFF; // Extract green
	uint8_t blue = (rgba >> 8) & 0xFF;   // Extract blue
	uint8_t alpha = rgba & 0xFF;         // Extract alpha
	return ((alpha << 24) | (blue << 16) | (green << 8) | red);
	// Reassemble in ARGB, swapping red and blue
}

void	draw_3d_col(t_game *game, double angle, float wall_height)
{
	double		min;
	int			index;
	float		texture_x;
	uint32_t	rgba_color;
	uint32_t	argb_color;

	int width, y, x, offset, texture_y, texture_index;
	index = FOV - 1;
	min = game->player->angle - (FOV / 2);
	while (min != angle)
	{
		min++;
		index--;
	}
	width = game->img_view_3d->width / (FOV - 1);
	texture_x = (float)(index % game->wall_image->width);
	offset = ((game->s_map.height / 2) - (wall_height / 2)) * TILE_SIZE;
	for (y = 0; y < (int)game->img_view_3d->height; y++)
	{
		x = (index * width);
		while (x < (index * width) + (width))
		{
			if (y >= offset && y < offset + wall_height * TILE_SIZE)
			{
				texture_y = ((float)(y - offset) / (wall_height * TILE_SIZE))
					* game->wall_image->height;
				if (texture_y >= (int)game->wall_image->height)
					texture_y = game->wall_image->height - 1;
				texture_index = (texture_y * game->wall_image->width
						+ (int)texture_x) % (game->wall_image->width
						* game->wall_image->height);
				rgba_color = ((uint32_t *)game->wall_image->pixels)[texture_index];
				argb_color = convert_rgba_to_argb(rgba_color);
				mlx_put_pixel(game->img_view_3d, x, y, argb_color);
			}
			else if (y < offset)
			{
				mlx_put_pixel(game->img_view_3d, x, y,
					ft_pixel(game->colors->ceiling[0], game->colors->ceiling[1],
						game->colors->ceiling[2], 0xFF));
			}
			else
			{
				mlx_put_pixel(game->img_view_3d, x, y,
					ft_pixel(game->colors->floor[0], game->colors->floor[1],
						game->colors->floor[2], 0xFF));
			}
			x++;
		}
	}
}

void	init_line_length(t_game *game)
{
	if (game->mlx->height > game->mlx->width)
		game->player->line->length = game->mlx->height / 2;
	else
		game->player->line->length = game->mlx->width / 2;
}

void	init_3d_view(t_game *game)
{
	game->img_view_3d = mlx_new_image(game->mlx, (game->s_map.width
				* TILE_SIZE), game->s_map.height * TILE_SIZE);
	mlx_image_to_window(game->mlx, game->img_view_3d, 0, 0);
	game->img_view_3d->instances[0].z = 0;
}

 void	update_line_position(t_direction_line *line)
{
	line->error2 = line->error * 2;
	if (line->error2 > -line->delta_y)
	{
		line->error -= line->delta_y;
		line->start_x += line->step_x;
	}
	if (line->error2 < line->delta_x)
	{
		line->error += line->delta_x;
		line->start_y += line->step_y;
	}
}

float	calculate_wall_height(t_game *game, float column_angle)
{
	t_direction_line	line;
	int					x;
	int					y;
	int					start_x;
	int					start_y;
	float				dist;

	/* game->player->line->img_line->instances[0].x = game->player->img_player->instances[0].x - line.length + game->player->img_player->width / 2;
	game->player->line->img_line->instances[0].y = game->player->img_player->instances[0].y - line.length + game->player->img_player->height / 2; */
	initialize_line_data(&line, column_angle, game);
	/* printf("PLAYER [%d] | [%d]\n", game->player->img_player->instances[0].y ,game->player->img_player->instances[0].x);
	printf("LINE [%d] | [%d]\n", game->player->line->img_line->instances[0].y ,game->player->line->img_line->instances[0].x); */
	start_x = line.start_x;
	start_y = line.start_y;
	//printf("start [%d][%d]\n", start_x, start_y);
	while (true)
	{
		//printf("[%d] [%d]\n", line.start_y, line.start_x);
		y = (game->player->line->img_line->instances[0].y + (line.start_y)) / (TILE_SIZE);
		x = (game->player->line->img_line->instances[0].x + (line.start_x)) / (TILE_SIZE);
		if (game->s_map.map[y] && game->s_map.map[y][x]
			&& game->s_map.map[y][x] == '1')
		{
			dist = sqrt(pow(line.start_x - start_x, 2)
					+ pow(line.start_y - start_y, 2));
		//			exit(1);
			return ((TILE_SIZE * game->s_map.height))
				/ (dist);
		}
		mlx_put_pixel(game->player->line->img_line, game->player->line->start_x,
			game->player->line->start_y, ft_pixel(255, 0, 0, 0xFF));
		update_line_position(&line);
	}
	
	return (-1);
}

void		start_drawing(t_game *game)
{
	int			column_nb;
	int			index;
	double		min;
	int			y;
	float		texture_y;
	float		texture_x;
	double		column_angle;
	float		columns_height;
	int			texture_index;
	uint32_t	rgba_color;
	uint32_t	argb_color;

	column_nb = game->img_view_3d->width;
	printf("col [%d]\n", column_nb);
	index = 1;
	min = game->player->angle - (FOV / 2);
	while (index < column_nb)
	{
		y = 0;
		texture_x = (float)(index % game->wall_image->width);
		column_angle = min + (index * FOV / column_nb);
		printf("COL [%f]\n", column_angle);
		//printf("colums_amglem [%f] ANGLE [%f]\n", column_angle, game->player->angle);
		columns_height = calculate_wall_height(game, column_angle) * TILE_SIZE;
        int y_start = (game->img_view_3d->height - columns_height) / 2; 
        int y_end = y_start + columns_height; 

        for (int y = y_start; y < y_end; y++) { 
            texture_y = ((float)(y - y_start) / columns_height) * game->wall_image->height;
            texture_index = ((int)texture_y * game->wall_image->width + (int)texture_x) % (game->wall_image->width * game->wall_image->height);
            rgba_color = ((uint32_t *)game->wall_image->pixels)[texture_index];
            argb_color = convert_rgba_to_argb(rgba_color);
            mlx_put_pixel(game->img_view_3d, index, y, argb_color);
        }
		index++;
	}
}

void	init_and_draw_lines(t_game *game)
{
	uint32_t	color;

	init_line_length(game);
	init_3d_view(game);
	color = ft_pixel(255, 0, 0, 0xFF);
	game->player->line->img_line = mlx_new_image(game->mlx,
			game->player->line->length * 2, game->player->line->length * 2);
	if (!game->player->line->img_line || (mlx_image_to_window(game->mlx,
				game->player->line->img_line, 0, 0) == -1))
		return (printf("Error\n"), (void)NULL);
	start_drawing(game);
	game->player->line->img_line->instances[0].z = 2;
	game->player->line->img_line[0].enabled = false;
}

void	set_depth_img(mlx_image_t *img, int z)
{
	unsigned int	x;

	x = 0;
	while (img->instances[x].z)
	{
		img->instances[x].z = z;
		x++;
	}
}

void	fill_by_pixel(mlx_image_t *img, int posY, int posX, int32_t color)
{
	int	y;
	int	x;

	y = posY + 1;
	while (y < posY + MAP_TILE_SIZE)
	{
		x = posX + 1;
		while (x < posX + MAP_TILE_SIZE)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	init_and_draw_map(t_game *game)
{
	unsigned int	y;
	unsigned int	x;

	game->s_map.image_map = mlx_new_image(game->mlx, game->s_map.width
			* MAP_TILE_SIZE, game->s_map.height * MAP_TILE_SIZE);
	y = 0;
	while (y < game->s_map.height)
	{
		x = 0;
		while (x < game->s_map.width && ft_strlen(game->s_map.map[y]) > x)
		{
			if (game->s_map.map[y][x] == '1')
				fill_by_pixel(game->s_map.image_map, (y * MAP_TILE_SIZE), (x
						* MAP_TILE_SIZE), ft_pixel(0, 0, 0, 0xFF));
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, game->s_map.image_map, 0, 0);
	game->s_map.image_map->instances[0].z = 3;
	game->s_map.image_map->instances[0].enabled = false;
}

void	draw_map2d(t_game *game)
{
	init_and_draw_player(game);
	init_and_draw_lines(game);
	init_and_draw_map(game);
}
