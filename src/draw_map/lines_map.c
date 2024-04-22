/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:56:00 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/22 14:17:56 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	color_img(mlx_image_t *img, uint32_t color, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	initialize_line_data(t_direction_line *line, double angle, t_game *game)
{
	float	angle_radians;

	line->start_x = game->player->line->length;
	line->start_y = game->player->line->length;
	angle_radians = angle * M_PI / 180.0;
	line->end_x = line->start_x + game->player->line->length
		* cos(angle_radians);
	line->end_y = line->start_y - game->player->line->length
		* sin(angle_radians);
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

static void	initialize_line(t_direction_line *line, mlx_image_t *img,
		t_game *game, double angle)
{
	initialize_line_data(line, angle, game);
	img->instances[0].x = game->player->img_player->instances[0].x
		- line->length + game->player->img_player->width / 2;
	img->instances[0].y = game->player->img_player->instances[0].y
		- line->length + game->player->img_player->height / 2;
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

void	draw_line_on_map(t_game *game, double angle)
{
	int			x;
	int			y;
	mlx_image_t	*img;

	img = game->player->line->img_line;
	initialize_line(game->player->line, img, game, angle);
	while (1)
	{
		y = (img->instances[0].y + game->player->line->start_y) / MAP_TILE_SIZE;
		x = (img->instances[0].x + game->player->line->start_x) / MAP_TILE_SIZE;
		if (game->s_map.map[y] && game->s_map.map[y][x]
			&& game->s_map.map[y][x] == '1')
			break ;
		mlx_put_pixel(img, game->player->line->start_x,
			game->player->line->start_y, ft_pixel(100, 255, 100, 0xFF));
		update_line_position(game->player->line);
	}
}
