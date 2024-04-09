/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:53:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 14:27:52 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	color_img(mlx_image_t *img, uint32_t color, int width, int height)
{
	int	x;
	int	y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
}

static mlx_image_t	*draw_player(mlx_t *mlx, t_point player)
{
	mlx_image_t	*img;
	uint32_t	color;

	color = ft_pixel(255, 0, 0, 0xFF);
	img = mlx_new_image(mlx, TILE_SIZE / 4, TILE_SIZE / 4);
	if (!img || (mlx_image_to_window(mlx, img, player.x * TILE_SIZE + TILE_SIZE
				/ 3, player.y * TILE_SIZE + +TILE_SIZE / 3) == -1))
		return (printf("Error\n"), NULL);
	color_img(img, color, TILE_SIZE / 4, TILE_SIZE / 4);
	img->instances[0].z = 1;
	return (img);
}

static mlx_image_t	*draw_wall(mlx_t *mlx, t_point wall)
{
	mlx_image_t	*img;
	uint32_t	color;

	color = ft_pixel(0, 0, 0, 0xFF);
	img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!img || (mlx_image_to_window(mlx, img, wall.x * TILE_SIZE - 1, wall.y
				* TILE_SIZE - 1) == -1))
		return (printf("Error\n"), NULL);
	color_img(img, color, TILE_SIZE - 1, TILE_SIZE - 1);
	img->instances[0].z = 2;
	return (img);
}

static mlx_image_t	*draw_void(mlx_t *mlx, t_point void_p)
{
	mlx_image_t	*img;
	uint32_t	color;

	color = ft_pixel(255, 255, 255, 0xFF);
	img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!img || (mlx_image_to_window(mlx, img, void_p.x * TILE_SIZE - 1,
				void_p.y * TILE_SIZE - 1) == -1))
		return (printf("Error\n"), NULL);
	color_img(img, color, TILE_SIZE - 1, TILE_SIZE - 1);
	img->instances[0].z = 0;
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

	game->player->img = draw_player(game->mlx, game->player->pos);
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
				if (!draw_wall(game->mlx, (t_point){x, y}))
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
