/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:56:00 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/17 19:52:24 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

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

static void	initialize_line(t_direction_line *line, mlx_image_t *img,
		t_game *game, double angle)
{
	img->instances[0].x = game->player->img_player->instances[0].x
		- line->length + game->player->img_player->width / 2;
	img->instances[0].y = game->player->img_player->instances[0].y
		- line->length + game->player->img_player->height / 2;
	initialize_line_data(line, angle, line->length);
}

static void	update_line_position(t_direction_line *line)
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

static int	process_line_drawing(mlx_image_t *img, t_game *game, uint32_t color,
		double angle)
{
	int		x;
	int		y;
	int		start_x;
	int		start_y;
	float	dist;

	start_x = game->player->line->start_x;
	start_y = game->player->line->start_y;
	while (true)
	{
		y = (img->instances[0].y + (game->player->line->start_y))
			/ (MAP_TILE_SIZE);
		x = (img->instances[0].x + game->player->line->start_x)
			/ (MAP_TILE_SIZE);
		if (game->s_map.map[y] && game->s_map.map[y][x]
			&& game->s_map.map[y][x] == '1')
		{
			dist = sqrt(pow(game->player->line->start_x - start_x, 2)
					+ pow(game->player->line->start_y - start_y, 2));
			draw_3d_col(game, angle, ((TILE_SIZE * game->s_map.height) / 2)
				/ (dist * 2));
			return (0);
		}
		mlx_put_pixel(img, game->player->line->start_x,
			game->player->line->start_y, color);
		update_line_position(game->player->line);
	}
	return (1);
}

void	color_line(mlx_image_t *img, uint32_t color, t_game *game, double angle)
{
	initialize_line(game->player->line, img, game, angle);
	if (!process_line_drawing(img, game, color, angle))
		return ;
}
