/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:53:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/14 13:15:41 by omar             ###   ########.fr       */
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
	img->instances[0].z = 2;
	return (img);
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

void	draw_3d_col(t_game *game, double angle, float wall_height)
{
	int		width;
	double	min;
	int		index;
	int		y;
	int		x;
	int		offset;

	index = 0;
	min = game->player->angle - 30;
	while (min != angle)
	{
		min++;
		index++;
	}
	width = game->img_view_3d->width / 60;
	y = 0;
	offset = ((game->s_map.height / 2) - (wall_height / 2)) * TILE_SIZE;
	while (y < (wall_height * TILE_SIZE))
	{
		x = index * width;
		while (x < (index * width) + width)
		{
			if (y + offset >= 0)
				mlx_put_pixel(game->img_view_3d, x, y + offset, ft_pixel(255, 0,
						0, 0xFF));
			x++;
		}
		y++;
	}
}

void	color_line(mlx_image_t *img, uint32_t color, t_game *game, double angle)
{
	int		y;
	int		x;
	float	dist;
	int		start_x;
	int		start_y;

	dist = 0;
	img->instances[0].x = game->player->img_player->instances[0].x
		- game->player->line->length + game->player->img_player->width / 2;
	img->instances[0].y = game->player->img_player->instances[0].y
		- game->player->line->length + game->player->img_player->height / 2;
	initialize_line_data(game->player->line, angle, game->player->line->length);
	start_x = game->player->line->start_x;
	start_y = game->player->line->start_y;
	while ((game->player->line->start_x != game->player->line->end_x
			|| game->player->line->start_y != game->player->line->end_y)
		&& (game->player->line->start_x >= 0
			&& game->player->line->start_x < (int)img->width
			&& game->player->line->start_y >= 0
			&& game->player->line->start_y < (int)img->height))
	{
		y = (img->instances[0].y + game->player->line->start_y) / TILE_SIZE;
		x = (img->instances[0].x + game->player->line->start_x) / TILE_SIZE;
		if (game->s_map.map[y] && game->s_map.map[y][x]
			&& game->s_map.map[y][x] == '1')
		{
			dist = sqrt(pow(game->player->line->start_x - start_x, 2)
					+ pow(game->player->line->start_y - start_y, 2));
			draw_3d_col(game, angle, (TILE_SIZE * game->s_map.height) / dist);
			return ;
		}
		mlx_put_pixel(img, game->player->line->start_x,
			game->player->line->start_y, color);
		game->player->line->error2 = game->player->line->error * 2;
		if (game->player->line->error2 > -game->player->line->delta_y)
		{
			game->player->line->error -= game->player->line->delta_y;
			game->player->line->start_x += game->player->line->step_x;
		}
		if (game->player->line->error2 < game->player->line->delta_x)
		{
			game->player->line->error += game->player->line->delta_x;
			game->player->line->start_y += game->player->line->step_y;
		}
	}
}

static void	init_line_length(mlx_t *mlx, t_game *game)
{
	if (mlx->height > mlx->width)
		game->player->line->length = mlx->height;
	else
		game->player->line->length = mlx->width;
}

static void	init_3d_view(mlx_t *mlx, t_game *game)
{
	game->img_view_3d = mlx_new_image(mlx, (game->s_map.width * TILE_SIZE),
			game->s_map.height * TILE_SIZE);
	mlx_image_to_window(mlx, game->img_view_3d, (game->s_map.width * TILE_SIZE),
		0);
}

static mlx_image_t	*draw_line(mlx_t *mlx, t_game *game)
{
	mlx_image_t	*img;
	uint32_t	color;
	double		i;

	init_line_length(mlx, game);
	init_3d_view(mlx, game);
	color = ft_pixel(255, 0, 0, 0xFF);
	img = mlx_new_image(mlx, game->player->line->length * 2,
			game->player->line->length * 2);
	if (!img || (mlx_image_to_window(mlx, img,
				game->player->img_player->instances[0].x
				- game->player->line->length + game->player->img_player->width
				/ 2, game->player->img_player->instances[0].y
				- game->player->line->length + game->player->img_player->height
				/ 2) == -1))
		return (printf("Error\n"), NULL);
	color_img(img, 0, img->width, img->height);
	i = game->player->angle - 30;
	while (i < game->player->angle + 30)
	{
		color_line(img, color, game, i);
		i++;
	}
	img->instances[0].z = 3;
	return (img);
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
	game->player->line->img_line = draw_line(game->mlx, game);
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
