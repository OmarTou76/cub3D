/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:10:28 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/28 11:58:08 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static uint32_t	get_pixel_from_texture(t_wall wall, int y)
{
	float	texture_x;
	float	texture_y;
	int		texture_index;
	float	fract_x;
	float	fract_y;

	fract_x = fmod(wall.collision_x, 1.0f);
	fract_y = fmod(wall.collision_y, 1.0f);
	if (fract_x < 0.95 || fract_y > 0.95)
		texture_x = fract_x;
	else
		texture_x = fract_y;
	texture_y = (float)y / wall.height;
	texture_index = ((int)(texture_y * wall.img->height) * wall.img->width)
		+ (int)(texture_x * wall.img->width);
	texture_index %= (wall.img->height * wall.img->width);
	return (convert_rgba_to_argb(((uint32_t *)wall.img->pixels)[texture_index]));
}

static void	draw_column(t_game *game, t_wall wall, int index)
{
	int			y_start;
	int			y;
	uint32_t	color;

	y_start = (game->img_view_3d->height - wall.height) / 2;
	y = 0;
	while (y < (int)game->img_view_3d->height)
	{
	// printf("y = %d\n", y);
	// printf("(int)game->img_view_3d->height = %d\n", (int)game->img_view_3d->height);
		if (y < y_start)
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, ft_pixel(game->colors->ceiling[0], game->colors->ceiling[1],
					game->colors->ceiling[2], 0xFF));
		else if (y > y_start + wall.height)
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, ft_pixel(game->colors->floor[0], game->colors->floor[1],
					game->colors->floor[2], 0xFF));
		else
		{
			color = get_pixel_from_texture(wall, y - y_start);
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, color);
		}
		y++;
	}
}

void	raycast(t_game *game)
{
	int		col_nb;
	int		index;
	float	right_angle;
	t_wall	wall;

	col_nb = game->img_view_3d->width; // Ex 645
	index = 0;
	right_angle = game->player->angle - (FOV / 2); // ex 90 - (60 / 2) = 90 -30 = 60
	while (index < col_nb)
	{
		get_wall(game, &wall, right_angle, index);
		draw_line_on_map(game, wall.column_angle);
		draw_column(game, wall, index);
		index++;
	}
}