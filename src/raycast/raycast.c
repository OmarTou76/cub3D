#include "cub3D.h"

double	compute_distance(t_game *game, double col_angle)
{
	t_direction_line	line;
	double				theta;
	double				y;
	double				x;
	double				step_y;
	double				step_x;

	line.start_x = game->player->img_player->instances[0].x;
	line.start_y = game->player->img_player->instances[0].y;
	y = game->player->img_player->instances[0].y;
	x = game->player->img_player->instances[0].x;
	theta = (-col_angle * M_PI) / 180.0;
	step_y = sin(theta) * .1;
	step_x = cos(theta) * .1;
	while (true)
	{
		if (game->s_map.map[(int)round(y) / TILE_SIZE][(int)round(x)
			/ TILE_SIZE] == '1')
			return (sqrt(pow(x - line.start_x, 2) + pow(y - line.start_y, 2)));
		x += step_x;
		y += step_y;
		update_line_position(game->player->line);
	}
	return (-1);
}

double	get_wall_height_and_draw_line(t_game *game, double left_angle,
		int index)
{
	int		column_count;
	double	col_angle;
	double	distance;

	column_count = game->img_view_3d->width;
	col_angle = left_angle + (index * FOV / column_count);
	distance = compute_distance(game, col_angle);
	/* Draw line in map
		- Do we need to call this function elsewhere? (we need <col_angle> property) */
	draw_line_on_map(game->player->line->img_line, game, col_angle);
	return ((TILE_SIZE * game->s_map.height) / distance) * (TILE_SIZE / 2);
}

uint32_t	get_pixel_from_texture(t_game *game, double col_height, int y,
		int x)
{
	float	texture_y;
	int		texture_index;

	texture_y = ((float)(y - (game->img_view_3d->height - col_height) / 2)
			/ col_height) * game->wall_image->height;
	texture_index = ((int)texture_y * game->wall_image->width + x)
		% (game->wall_image->width * game->wall_image->height);
	return (convert_rgba_to_argb(((uint32_t *)game->wall_image->pixels)[texture_index]));
}

void	draw_column(t_game *game, int index, double col_height)
{
	int	texture_x;
	int	y;
	int	y_start;

	texture_x = (index % game->wall_image->width);
	y_start = (game->img_view_3d->height - col_height) / 2;
	y = 0;
	while (y < (int)game->img_view_3d->height)
	{
		if (y >= y_start && y <= y_start + col_height)
		{
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, get_pixel_from_texture(game, col_height, y, texture_x));
		}
		else if (y < y_start)
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, ft_pixel(game->colors->ceiling[0], game->colors->ceiling[1],
					game->colors->ceiling[2], 0xFF));
		else if (y > y_start + col_height)
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, ft_pixel(game->colors->floor[0], game->colors->floor[1],
					game->colors->floor[2], 0xFF));
		y++;
	}
}

void	raycast(t_game *game)
{
	int		col_nb;
	int		index;
	double	left_angle;
	double	col_height;

	col_nb = game->img_view_3d->width;
	index = 1;
	left_angle = game->player->angle - (FOV / 2);
	while (index < col_nb)
	{
		col_height = get_wall_height_and_draw_line(game, left_angle, index);
		draw_column(game, index, col_height);
		index++;
	}
}
