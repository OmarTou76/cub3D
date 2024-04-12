/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:53:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/12 12:36:40 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	color_img(mlx_image_t *img, uint32_t color, int width, int height)
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

static mlx_image_t	*draw_wall(mlx_t *mlx, t_point wall)
{
	mlx_image_t	*img;
	uint32_t	color;

	color = ft_pixel(0, 0, 0, 0xFF);
	img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!img || (mlx_image_to_window(mlx, img, wall.x * TILE_SIZE + 1, wall.y
				* TILE_SIZE + 1) == -1))
		return (printf("Error\n"), NULL);
	color_img(img, color, TILE_SIZE - 1, TILE_SIZE - 1);
	img->instances[0].z = 5;
	return (img);
}

static mlx_image_t	*draw_background(mlx_t *mlx, t_point wall)
{
	mlx_image_t	*img;
	uint32_t	color;

	color = ft_pixel(155, 155, 155, 0xFF);
		img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!img || (mlx_image_to_window(mlx, img, wall.x * TILE_SIZE, wall.y
				* TILE_SIZE) == -1))
		return (printf("Error\n"), NULL);
	color_img(img, color, TILE_SIZE, TILE_SIZE);
	img->instances[0].z = 4;
	return (img);
}

static mlx_image_t	*draw_void(mlx_t *mlx, t_point void_p)
{
	mlx_image_t	*img;
	uint32_t	color;

	color = ft_pixel(255, 255, 255, 0xFF);
	img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!img || (mlx_image_to_window(mlx, img, void_p.x * TILE_SIZE + 1,
				void_p.y * TILE_SIZE + 1) == -1))
		return (printf("Error\n"), NULL);
	color_img(img, color, TILE_SIZE - 1, TILE_SIZE - 1);
	img->instances[0].z = 1;
	return (img);
}

	typedef struct s_line_data
	{
		int				start_x;
		int				start_y;
		int				end_x;
		int				end_y;
		int				delta_x;
		int				delta_y;
		int				step_x;
		int				step_y;
		int				error;
		int				error2;
	}					t_line_data;

	void	initialize_line_data(t_line_data *line_data, t_player *player)
	{
		float	angle_radians;

		line_data->start_x = LINE_HEIGHT;
		line_data->start_y = LINE_HEIGHT;
		angle_radians = player->angle * M_PI / 180.0;
		line_data->end_x = line_data->start_x + (int)(LINE_HEIGHT
				* cos(angle_radians));
		line_data->end_y = line_data->start_y - (int)(LINE_HEIGHT
				* sin(angle_radians));
		line_data->delta_x = abs(line_data->end_x - line_data->start_x);
		line_data->delta_y = abs(line_data->end_y - line_data->start_y);
		if(line_data->start_x < line_data->end_x)
			line_data->step_x = 1;
		else
			line_data->step_x = -1;
		if(line_data->start_y < line_data->end_y)
			line_data->step_y = 1;
		else
			line_data->step_y = -1;
		line_data->error = line_data->delta_x - line_data->delta_y;
	}

	void	color_line(mlx_image_t *img, uint32_t color, t_player *player)
	{
		t_line_data	line_data;

		img->instances[0].x = player->img_player->instances[0].x - LINE_HEIGHT
			+ player->img_player->width / 2;
		img->instances[0].y = player->img_player->instances[0].y - LINE_HEIGHT
			+ player->img_player->height / 2;
		color_img(img, 0, img->width, img->height);
		initialize_line_data(&line_data, player);
		while ((line_data.start_x != line_data.end_x
				|| line_data.start_y != line_data.end_y) && (line_data.start_x >= 0
				&& line_data.start_x < (int)img->width && line_data.start_y >= 0
				&& line_data.start_y < (int)img->height))
		{
			mlx_put_pixel(img, line_data.start_x, line_data.start_y, color);
			line_data.error2 = line_data.error * 2;
			if (line_data.error2 > -line_data.delta_y)
			{
				line_data.error -= line_data.delta_y;
				line_data.start_x += line_data.step_x;
			}
			if (line_data.error2 < line_data.delta_x)
			{
				line_data.error += line_data.delta_x;
				line_data.start_y += line_data.step_y;
			}
		}
	}

	static mlx_image_t	*draw_line(mlx_t *mlx, t_player *player)
	{
		mlx_image_t	*img;
		uint32_t	color;

		color = ft_pixel(255, 0, 0, 0xFF);
		img = mlx_new_image(mlx, LINE_HEIGHT * 2, LINE_HEIGHT * 2);
		if (!img || (mlx_image_to_window(mlx, img,
					player->img_player->instances[0].x - LINE_HEIGHT
					+ player->img_player->width / 2,
					player->img_player->instances[0].y - LINE_HEIGHT
					+ player->img_player->height / 2) == -1))
			return (printf("Error\n"), NULL);
		// color_img(img, color, LINE_HEIGHT * 2, LINE_HEIGHT * 2);
		color_line(img, color, player);
		img->instances[0].z = 2;
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

int	draw_map2d(t_game *game)
{
	unsigned int	x;
	unsigned int	y;

	game->player->img_player = draw_player(game->mlx, game->player);
	game->player->img_line = draw_line(game->mlx, game->player);
	if (!draw_void(game->mlx, game->player->pos))
		return (0);
	y = 0;
	while (y < game->s_map.height)
	{
		x = 0;
		while (x < game->s_map.width && ft_strlen(game->s_map.map[y]) > x)
		{
			if (game->s_map.map[y][x] == '1')
			{
				if (!draw_wall(game->mlx, (t_point){x, y}) || !draw_background(game->mlx, (t_point){x, y}))
					return (0);
			}
			else if (game->s_map.map[y][x] == '0')
			{
				if (!draw_void(game->mlx, (t_point){x, y}))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
