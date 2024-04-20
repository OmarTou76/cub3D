/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:53:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/21 00:10:53 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_and_draw_player(mlx_t *mlx, t_game *game)
{
	uint32_t	color;

	color = ft_pixel(255, 0, 0, 0xFF);
	game->player->img_player = mlx_new_image(mlx, PLAYER_SIZE, PLAYER_SIZE);
	mlx_image_to_window(mlx, game->player->img_player, game->player->pos.x
		* TILE_SIZE + TILE_SIZE / 2 - PLAYER_SIZE / 2, game->player->pos.y
		* TILE_SIZE + TILE_SIZE / 2 - PLAYER_SIZE / 2);
	color_img(game->player->img_player, color, PLAYER_SIZE, PLAYER_SIZE);
	game->player->img_player->instances[0].z = 1;
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

void	init_and_draw_line_and_raycast(mlx_t *mlx, t_game *game)
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
	game->player->img_player->instances[0].z = 2;
	raycast(game);
}

void	fill_by_pixel(mlx_image_t *img, int posY, int posX, int32_t color)
{
	int	y;
	int	x;

	y = posY + 1;
	while (y < posY + TILE_SIZE)
	{
		x = posX + 1;
		while (x < posX + TILE_SIZE)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	init_and_draw_map(t_game *game)
{
	unsigned int	y;
	unsigned int	x;

	game->s_map.img_map = mlx_new_image(game->mlx, game->s_map.width
			* TILE_SIZE, game->s_map.height * TILE_SIZE);
	y = 0;
	while (y < game->s_map.height)
	{
		x = 0;
		while (x < game->s_map.width && ft_strlen(game->s_map.map[y]) > x)
		{
			if (game->s_map.map[y][x] == '1')
				fill_by_pixel(game->s_map.img_map, (y * TILE_SIZE), (x
						* TILE_SIZE), ft_pixel(0, 0, 0, 0xFF));
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, game->s_map.img_map, 0, 0);
}

void	init_game(t_game *game)
{
	init_and_draw_player(game->mlx, game);
	init_and_draw_map(game);
	init_and_draw_line_and_raycast(game->mlx, game);
}