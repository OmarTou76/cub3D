/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:53:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/05 02:38:47 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void init_and_draw_player(mlx_t *mlx, t_game *game)
{
	uint32_t color;

	color = ft_pixel(255, 0, 0, 0xFF);
	game->player->img_player = mlx_new_image(mlx, game->s_map.player_size, game->s_map.player_size);
	int paddingY = (WINDOW_HEIGHT - game->s_map.img_map->height) / 2;
	int paddingX = (WINDOW_WIDTH - game->s_map.img_map->width) / 2;
	mlx_image_to_window(mlx, game->player->img_player, (game->player->pos.x * game->s_map.tile_size) + paddingX + game->s_map.tile_size / 2 - game->s_map.player_size / 2,
						game->player->pos.y * game->s_map.tile_size + paddingY + game->s_map.tile_size / 2 - game->s_map.player_size / 2);
	color_img(game->player->img_player, color, game->s_map.player_size, game->s_map.player_size);
	mlx_set_instance_depth(game->player->img_player->instances, 1);
	game->player->img_player->enabled = false;
}

static void init_line_length(t_game *game)
{
	if (game->s_map.img_map->height > game->s_map.img_map->width)
		game->player->line->length = game->s_map.img_map->height;
	else
		game->player->line->length = game->s_map.img_map->width;
}

static void init_3d_view(mlx_t *mlx, t_game *game)
{
	game->img_view_3d = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(mlx, game->img_view_3d, 0, 0);
	mlx_set_instance_depth(game->img_view_3d->instances, 1);
	mlx_resize_image(game->textures.pistol[0], game->img_view_3d->width / 2, game->img_view_3d->height / 2);
	mlx_resize_image(game->textures.pistol[1], game->img_view_3d->width / 2, game->img_view_3d->height / 2);
	mlx_resize_image(game->textures.pistol[2], game->img_view_3d->width / 2, game->img_view_3d->height / 2);
	mlx_resize_image(game->textures.pistol[3], game->img_view_3d->width / 2, game->img_view_3d->height / 2);
	mlx_image_to_window(mlx, game->textures.pistol[0], game->img_view_3d->width / 2, game->img_view_3d->height / 2);
	mlx_image_to_window(mlx, game->textures.pistol[1], game->img_view_3d->width / 2, game->img_view_3d->height / 2);
	mlx_image_to_window(mlx, game->textures.pistol[2], game->img_view_3d->width / 2, game->img_view_3d->height / 2);
	mlx_image_to_window(mlx, game->textures.pistol[3], game->img_view_3d->width / 2, game->img_view_3d->height / 2);
	game->textures.pistol[1]->enabled = false;
	game->textures.pistol[2]->enabled = false;
	game->textures.pistol[3]->enabled = false;

	mlx_resize_image(game->textures.reticle, game->img_view_3d->width / 15, game->img_view_3d->height / 15);
	mlx_image_to_window(mlx, game->textures.reticle, game->img_view_3d->width / 2 - game->textures.reticle->width / 2, game->img_view_3d->height / 2  - game->textures.reticle->height / 2);
	mlx_set_instance_depth(game->textures.pistol[0]->instances, 2);
	mlx_set_instance_depth(game->textures.reticle->instances, 3);
}

static void init_and_draw_line(mlx_t *mlx, t_game *game)
{
	init_line_length(game);
	game->player->line->img_line = mlx_new_image(mlx, game->player->line->length * 2, game->player->line->length * 2);

	mlx_image_to_window(mlx,
						game->player->line->img_line,
						0, 0);
	mlx_set_instance_depth(game->player->line->img_line->instances, 3);
	game->player->line->img_line->enabled = false;
}

void fill_by_pixel(t_map map, int posY, int posX, int32_t color)
{
	int y;
	int x;

	y = posY;
	while (y < posY + map.tile_size)
	{
		x = posX;
		while (x < posX + map.tile_size)
		{
			mlx_put_pixel(map.img_map, x, y, color);
			x++;
		}
		y++;
	}
}

static void init_and_draw_map(t_game *game)
{
	unsigned int y;
	unsigned int x;

	game->s_map.img_map = mlx_new_image(game->mlx, (game->s_map.width * game->s_map.tile_size), game->s_map.height * game->s_map.tile_size);
	y = 0;
	while (y < game->s_map.height)
	{
		x = 0;
		while (x < game->s_map.width && ft_strlen(game->s_map.map[y]) > x)
		{

			if (game->s_map.map[y][x] == '1' || game->s_map.map[y][x] == 'D')
				fill_by_pixel(game->s_map, (y * game->s_map.tile_size), (x * game->s_map.tile_size), ft_pixel(0, 0, 0, 0xFF));
			else
				fill_by_pixel(game->s_map, (y * game->s_map.tile_size), (x * game->s_map.tile_size), ft_pixel(150, 150, 150, 0x90));
			x++;
		}
		y++;
	}
	int paddingY = (WINDOW_HEIGHT - game->s_map.img_map->height) / 2;
	int paddingX = (WINDOW_WIDTH - game->s_map.img_map->width) / 2;
	mlx_image_to_window(game->mlx, game->s_map.img_map, paddingX, paddingY);
	mlx_set_instance_depth(game->s_map.img_map->instances, 2);
	game->s_map.img_map->enabled = false;
}

bool init_game(t_game *game)
{
	if (!init_and_load_textures(game))
		return (false);
	init_and_draw_map(game);
	init_and_draw_player(game->mlx, game);
	init_and_draw_line(game->mlx, game);
	init_3d_view(game->mlx, game);
	raycast(game);
	return (true);
}