/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:55:43 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 00:40:49 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_and_draw_player(mlx_t *mlx, t_game *game)
{
	uint32_t	color;
	int			center;

	color = ft_pixel(255, 0, 0, 0xFF);
	center = (int)round(game->map.tile_size / 3);
	game->player->img_player = mlx_new_image(mlx, game->map.player_size,
			game->map.player_size);
	mlx_image_to_window(mlx, game->player->img_player, (game->player->pos.x
			* game->map.tile_size + game->map.padding_x) + center,
		(game->player->pos.y * game->map.tile_size + game->map.padding_y)
		+ center);
	color_img(game->player->img_player, color, game->map.player_size,
		game->map.player_size);
	mlx_set_instance_depth(game->player->img_player->instances, 1);
	game->player->img_player->enabled = false;
	game->player->moves = false;
}

static void	resize_textures(mlx_t *mlx, t_game *game)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		mlx_resize_image(game->animation.pistol[i], game->img_view_3d->width
			/ 2, game->img_view_3d->height / 2);
		mlx_image_to_window(mlx, game->animation.pistol[i],
			game->img_view_3d->width / 2, game->img_view_3d->height / 2);
		mlx_set_instance_depth(game->animation.pistol[i]->instances, 2);
		if (i != 0)
			game->animation.pistol[i]->enabled = false;
		i++;
	}
	mlx_resize_image(game->animation.reticle, game->img_view_3d->width / 15,
		game->img_view_3d->height / 15);
	mlx_image_to_window(mlx, game->animation.reticle, game->img_view_3d->width
		/ 2 - game->animation.reticle->width / 2, game->img_view_3d->height / 2
		- game->animation.reticle->height / 2);
	mlx_set_instance_depth(game->animation.reticle->instances, 3);
}

static void	init_3d_view(mlx_t *mlx, t_game *game)
{
	game->img_view_3d = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(mlx, game->img_view_3d, 0, 0);
	mlx_set_instance_depth(game->img_view_3d->instances, 1);
}

bool	init_and_draw_game(t_game *game)
{
	if (!init_and_load_textures(game))
		return (false);
	init_and_draw_map(game);
	init_and_draw_line(game->mlx, game);
	init_and_draw_player(game->mlx, game);
	init_3d_view(game->mlx, game);
	resize_textures(game->mlx, game);
	raycast(game);
	return (true);
}
