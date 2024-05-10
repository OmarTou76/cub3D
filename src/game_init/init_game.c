/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:53:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/11 00:53:47 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_and_draw_player(mlx_t *mlx, t_game *game)
{
	uint32_t	color;

	color = ft_pixel(255, 0, 0, 0xFF);
	game->player->img_player = mlx_new_image(mlx, game->map.player_size,
			game->map.player_size);
	mlx_image_to_window(mlx, game->player->img_player, ((game->player->pos.x
				* game->map.tile_size) + game->map.padding_x),
		(game->player->pos.y * game->map.tile_size) + game->map.padding_y);
	color_img(game->player->img_player, color, game->map.player_size,
		game->map.player_size);
	mlx_set_instance_depth(game->player->img_player->instances, 1);
	game->player->img_player->enabled = false;
}

static void	resize_animation_textures(mlx_t *mlx, t_game *game)
{
	mlx_resize_image(game->animation.pistol[0], game->img_view_3d->width / 2,
		game->img_view_3d->height / 2);
	mlx_resize_image(game->animation.pistol[1], game->img_view_3d->width / 2,
		game->img_view_3d->height / 2);
	mlx_resize_image(game->animation.pistol[2], game->img_view_3d->width / 2,
		game->img_view_3d->height / 2);
	mlx_resize_image(game->animation.pistol[3], game->img_view_3d->width / 2,
		game->img_view_3d->height / 2);
	mlx_image_to_window(mlx, game->animation.pistol[0], game->img_view_3d->width
		/ 2, game->img_view_3d->height / 2);
	mlx_image_to_window(mlx, game->animation.pistol[1], game->img_view_3d->width
		/ 2, game->img_view_3d->height / 2);
	mlx_image_to_window(mlx, game->animation.pistol[2], game->img_view_3d->width
		/ 2, game->img_view_3d->height / 2);
	mlx_image_to_window(mlx, game->animation.pistol[3], game->img_view_3d->width
		/ 2, game->img_view_3d->height / 2);
	game->animation.pistol[1]->enabled = false;
	game->animation.pistol[2]->enabled = false;
	game->animation.pistol[3]->enabled = false;
	mlx_resize_image(game->animation.reticle, game->img_view_3d->width / 15,
		game->img_view_3d->height / 15);
	mlx_image_to_window(mlx, game->animation.reticle, game->img_view_3d->width
		/ 2 - game->animation.reticle->width / 2, game->img_view_3d->height / 2
		- game->animation.reticle->height / 2);
	mlx_set_instance_depth(game->animation.pistol[0]->instances, 2);
	mlx_set_instance_depth(game->animation.pistol[1]->instances, 2);
	mlx_set_instance_depth(game->animation.pistol[2]->instances, 2);
	mlx_set_instance_depth(game->animation.pistol[3]->instances, 2);
	mlx_set_instance_depth(game->animation.reticle->instances, 3);
}
static void	init_3d_view(mlx_t *mlx, t_game *game)
{
	game->img_view_3d = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(mlx, game->img_view_3d, 0, 0);
	mlx_set_instance_depth(game->img_view_3d->instances, 1);
}

void	fill_by_pixel(t_map map, int posY, int posX, int32_t color)
{
	int	y;
	int	x;

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

bool	init_game(t_game *game)
{
	if (!init_and_load_textures(game))
		return (false);
	init_and_draw_map(game);
	init_and_draw_player(game->mlx, game);
	init_and_draw_line(game->mlx, game);
	init_3d_view(game->mlx, game);
	resize_animation_textures(game->mlx, game);
	raycast(game);
	return (true);
}
