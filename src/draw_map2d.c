/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:53:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/07 22:11:30 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	color_img(mlx_image_t *img, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	while (x < TILE_SIZE)
	{
		y = 0;
		while (y < TILE_SIZE)
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
	img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!img || (mlx_image_to_window(mlx, img, player.x * TILE_SIZE, player.y
				* TILE_SIZE) == -1))
		printf("Error\n");
	color_img(img, color);
	return (img);
}

int	draw_map_2D(t_game *game)
{
	unsigned int x;
	unsigned int y;
	mlx_image_t *img_wall;
	mlx_image_t *img_void;
	uint32_t color;

	color = ft_pixel(0, 0, 0, 0xFF);
	game->img_player = draw_player(game->mlx, game->s_map.player);
	img_wall = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!img_wall)
		return (printf("Error\n"), -1);
	img_void = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!img_void)
		return (printf("Error\n"), -1);
	x = 0;
	while (x < game->s_map.width)
	{
		y = 0;
		while (y < game->s_map.height)
		{
			if (game->s_map.map[y][x] == '1')
			{
				if (mlx_image_to_window(game->mlx, img_wall, x * TILE_SIZE, y
						* TILE_SIZE) == -1)
					return (printf("Error\n"), -1);
				color_img(img_wall, color);
			}
			else if (game->s_map.map[y][x] == '0')
			{
				if (mlx_image_to_window(game->mlx, img_void, x * TILE_SIZE, y
						* TILE_SIZE) == -1)
					return (printf("Error\n"), -1);
				color_img(img_void, ft_pixel(255, 255, 255, 0xFF));
			}
			y++;
		}
		x++;
	}
	return (0);
}