/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:10:28 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 20:36:52 by ymeziane         ###   ########.fr       */
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
	if (fract_x < 0.99 && fract_x > 0.01)
		texture_x = fract_x;
	else
		texture_x = fract_y;
	texture_y = (float)y / wall.height;
	texture_index = ((int)(texture_y * wall.img->height) * wall.img->width)
		+ (int)(texture_x * wall.img->width);
	texture_index %= (wall.img->height * wall.img->width);
	return (convert_rgba_to_argb(((uint32_t *)wall.img->pixels)
			[texture_index]));
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
			if (!(wall.crack && (int)color == 0))
				mlx_put_pixel(game->img_view_3d, game->img_view_3d->width
					- index, y, color);
		}
		y++;
	}
}

static void	duplicate_wall(t_wall wall, t_wall *door)
{
	door->collision_x = wall.collision_x;
	door->collision_y = wall.collision_y;
	door->collision_x = wall.last_collision_x;
	door->collision_y = wall.last_collision_y;
	door->column_angle = wall.column_angle;
	door->height = wall.height;
	door->crack = true;
}

void	raycast(t_game *game)
{
	int		col_nb;
	int		index;
	float	right_angle;
	t_wall	wall;
	t_wall	door;

	col_nb = game->img_view_3d->width;
	index = col_nb;
	right_angle = game->player->angle - (FOV / 2);
	wall.img = NULL;
	door.img = game->animation.crack;
	while (index > 0)
	{
		get_wall(game, &wall, right_angle, index);
		draw_column(game, wall, index);
		if (wall.crack)
		{
			duplicate_wall(wall, &door);
			draw_column(game, door, index);
			wall.crack = false;
		}
		index--;
	}
}
