/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:53:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/20 22:35:35 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static mlx_image_t	*draw_player(mlx_t *mlx, t_player *player)
{
	mlx_image_t	*img;
	uint32_t	color;

	color = ft_pixel(255, 0, 0, 0xFF);
	img = mlx_new_image(mlx, PLAYER_SIZE, PLAYER_SIZE);
	if (!img || (mlx_image_to_window(mlx, img, player->pos.x * TILE_SIZE
				+ TILE_SIZE / 2 - PLAYER_SIZE / 2, player->pos.y * TILE_SIZE
				+ TILE_SIZE / 2 - PLAYER_SIZE / 2) == -1))
		return (printf("Error\n"), NULL);
	color_img(img, color, PLAYER_SIZE, PLAYER_SIZE);
	img->instances[0].z = 1;
	return (img);
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

void	draw_3d_col(t_game *game, double angle, float wall_height)
{
	int		width;
	double	min;
	int		index;
	int		y;
	int		x;
	int		offset;

	index = 59;
	min = game->player->angle - 30;
	while (min != angle)
	{
		min++;
		index--;
	}
	width = game->img_view_3d->width / 60;
	y = 0;
	offset = ((game->s_map.height / 2) - (wall_height / 2)) * TILE_SIZE;
	while (y < (int)game->img_view_3d->height)
	{
		x = (index * width);
		while (x < (index * width) + width)
		{
			if ((y < wall_height * TILE_SIZE && y + offset >= 0))
			{
				mlx_put_pixel(game->img_view_3d, x, y + offset, ft_pixel(255, 0,
						0, 0xFF));
			}
			if (y < offset)
				mlx_put_pixel(game->img_view_3d, x, y,
					ft_pixel(game->colors->ceiling[0], game->colors->ceiling[1],
						game->colors->ceiling[2], 0xFF));
			else if (y > offset + wall_height * TILE_SIZE)
				mlx_put_pixel(game->img_view_3d, x, y,
					ft_pixel(game->colors->floor[0], game->colors->floor[1],
						game->colors->floor[2], 0xFF));
			else
				mlx_put_pixel(game->img_view_3d, x, y, ft_pixel(255, 0, 0,
						0xFF));
			x++;
		}
		y++;
	}
}

static void	init_line_length(mlx_t *mlx, t_game *game)
{
	if (mlx->height > mlx->width)
		game->player->line->length = mlx->height / 2;
	else
		game->player->line->length = mlx->width / 2;
}

static void	init_3d_view(mlx_t *mlx, t_game *game)
{
	game->img_view_3d = mlx_new_image(mlx, (game->s_map.width * TILE_SIZE),
			game->s_map.height * TILE_SIZE);
	mlx_image_to_window(mlx, game->img_view_3d, (game->s_map.width * TILE_SIZE),
		0);
}

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

uint32_t	convert_rgba_to_argb(uint32_t rgba)
{
	uint8_t red = (rgba >> 24) & 0xFF;   // Extract red
	uint8_t green = (rgba >> 16) & 0xFF; // Extract green
	uint8_t blue = (rgba >> 8) & 0xFF;   // Extract blue
	uint8_t alpha = rgba & 0xFF;         // Extract alpha
	return ((alpha << 24) | (blue << 16) | (green << 8) | red);
	// Reassemble in ARGB, swapping red and blue
}

void	raycast(t_game *game)
{
	int			col_nb;
	int			index;
	double		min;
	double		col_angle;
	double		distance;
	int			col_height;
	float		texture_x;
	float		texture_y;
	int			texture_index;
	uint32_t	rgba_color;
	uint32_t	argb_color;
	int			y;
	int			y_start;

	col_nb = game->img_view_3d->width;
	index = 1;
	min = game->player->angle - (FOV / 2);
	while (index < col_nb)
	{
		col_angle = min + (index * FOV / col_nb);
		texture_x = (float)(index % game->wall_image->width);
		distance = compute_distance(game, col_angle);
		col_height = ((TILE_SIZE * game->s_map.height) / distance) * (TILE_SIZE
				/ 2);
		y_start = (game->img_view_3d->height - col_height) / 2;
		y = 0;
		while (y < (int)game->img_view_3d->height)
		{
			if (y >= y_start && y <= y_start + col_height)
			{
				texture_y = ((float)(y - (game->img_view_3d->height
								- col_height) / 2) / col_height)
					* game->wall_image->height;
				texture_index = ((int)texture_y * game->wall_image->width
						+ (int)texture_x) % (game->wall_image->width
						* game->wall_image->height);
				rgba_color = ((uint32_t *)game->wall_image->pixels)[texture_index];
				argb_color = convert_rgba_to_argb(rgba_color);
				mlx_put_pixel(game->img_view_3d, game->img_view_3d->width
					- index, y, argb_color);
			}
			else if (y < y_start)
				mlx_put_pixel(game->img_view_3d, game->img_view_3d->width
					- index, y, ft_pixel(game->colors->ceiling[0],
						game->colors->ceiling[1], game->colors->ceiling[2],
						0xFF));
			else if (y > y_start + col_height)
				mlx_put_pixel(game->img_view_3d, game->img_view_3d->width
					- index, y, ft_pixel(game->colors->floor[0],
						game->colors->floor[1], game->colors->floor[2], 0xFF));
			y++;
		}
		color_line(game->player->line->img_line, ft_pixel(50, 100, 150, 0xFF),
			game, col_angle);
		index++;
	}
}

void	draw_line(mlx_t *mlx, t_game *game)
{
	init_line_length(mlx, game);
	init_3d_view(mlx, game);
	game->player->line->img_line = mlx_new_image(mlx, game->player->line->length
			* 2, game->player->line->length * 2);
	if (!game->player->line->img_line || (mlx_image_to_window(mlx,
				game->player->line->img_line,
				game->player->img_player->instances[0].x
				- game->player->line->length + game->player->img_player->width
				/ 2, game->player->img_player->instances[0].y
				- game->player->line->length + game->player->img_player->height
				/ 2) == -1))
		return (printf("Error\n"), (void)NULL);
	raycast(game);
	game->player->img_player->instances[0].z = 2;
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

static mlx_image_t	*draw_img(mlx_t *mlx, t_point pos, uint32_t color, int z)
{
	mlx_image_t	*img;
	int			add;

	add = (z != 4);
	img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!img || (mlx_image_to_window(mlx, img, pos.x * TILE_SIZE + add, pos.y
				* TILE_SIZE + add) == -1))
		return (printf("Error\n"), NULL);
	color_img(img, color, TILE_SIZE - add, TILE_SIZE - add);
	img->instances[0].z = z;
	return (img);
}

int	draw_map2d(t_game *game)
{
	unsigned int	x;
	unsigned int	y;

	game->player->img_player = draw_player(game->mlx, game->player);
	draw_line(game->mlx, game);
	if (!draw_img(game->mlx, game->player->pos, ft_pixel(255, 255, 255, 0xFF),
			1))
		return (0);
	y = 0;
	while (y < game->s_map.height)
	{
		x = 0;
		while (x < game->s_map.width && ft_strlen(game->s_map.map[y]) > x)
		{
			if (game->s_map.map[y][x] == '1')
			{
				if (!draw_img(game->mlx, (t_point){x, y}, ft_pixel(0, 0, 0,
							0xFF), 5) || !draw_img(game->mlx, (t_point){x, y},
						ft_pixel(155, 155, 155, 0xFF), 4))
					return (0);
			}
			else if (game->s_map.map[y][x] == '0')
			{
				if (!draw_img(game->mlx, (t_point){x, y}, ft_pixel(255, 255,
							255, 0xFF), 0))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
