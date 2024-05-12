/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:19:31 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 20:40:46 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_game(t_game *game)
{
	if (game != NULL)
	{
		free(game->map.map);
		free(game->colors);
		free(game->paths);
		free(game->player);
		free(game);
	}
}

void	free_nodes(t_lines *node)
{
	t_lines	*tmp;

	while (node)
	{
		tmp = node->next;
		free(node->line);
		free(node);
		node = tmp;
	}
}

void	free_vecs(t_vec *vecs)
{
	t_vec	*tmp;

	while (vecs)
	{
		tmp = vecs->next;
		free(vecs);
		vecs = tmp;
	}
}

static void	delete_animated_image(t_game *game)
{
	int	i;

	i = -1;
	if (game->animation.crack != NULL)
		mlx_delete_image(game->mlx, game->animation.crack);
	if (game->animation.reticle != NULL)
		mlx_delete_image(game->mlx, game->animation.reticle);
	while (++i < 4)
		if (game->animation.pistol[i] != NULL)
			mlx_delete_image(game->mlx, game->animation.pistol[i]);
}

void	delete_images(t_game *game)
{
	if (game->textures.east != NULL)
		mlx_delete_image(game->mlx, game->textures.east);
	if (game->textures.west != NULL)
		mlx_delete_image(game->mlx, game->textures.west);
	if (game->textures.south != NULL)
		mlx_delete_image(game->mlx, game->textures.north);
	if (game->textures.north != NULL)
		mlx_delete_image(game->mlx, game->textures.north);
	if (game->img_view_3d != NULL)
		mlx_delete_image(game->mlx, game->img_view_3d);
	if (game->map.rays.img_line != NULL)
		mlx_delete_image(game->mlx, game->map.rays.img_line);
	if (game->player->img_player != NULL)
		mlx_delete_image(game->mlx, game->player->img_player);
	if (game->map.img_map != NULL)
		mlx_delete_image(game->mlx, game->map.img_map);
	delete_animated_image(game);
}
