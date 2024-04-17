/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:53:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/17 14:32:03 by omar             ###   ########.fr       */
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
		unsigned int line_height)
{
	float	angle_radians;

	line->start_x = line_height;
	line->start_y = line_height;
	angle_radians = angle * M_PI / 180.0;
	line->end_x = line->start_x + line_height * cos(angle_radians);
	line->end_y = line->start_y - line_height * sin(angle_radians);
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
	float		texture_x;
	uint32_t	rgba_color;
	uint32_t	argb_color;

	int width, index, y, x, offset, texture_y, texture_index;
	index = 59;
	min = game->player->angle - 30;
	while (min != angle)
	{
		min++;
		index--;
	}
	width = game->img_view_3d->width / 59;
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

void	init_and_draw_lines(t_game *game)
{
	uint32_t	color;
	double		i;

	init_line_length(game);
	init_3d_view(game);
	color = ft_pixel(255, 0, 0, 0xFF);
	game->player->line->img_line = mlx_new_image(game->mlx,
			game->player->line->length * 2, game->player->line->length * 2);
	if (!game->player->line->img_line || (mlx_image_to_window(game->mlx,
				game->player->line->img_line, 0, 0) == -1))
		return (printf("Error\n"), (void)NULL);
	i = game->player->angle - 30;
	while (i < game->player->angle + 30)
	{
		color_line(game->player->line->img_line, color, game, i);
		i++;
	}
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
