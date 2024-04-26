/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:19:31 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/26 19:32:13 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_game(t_game *game)
{
	if (game != NULL)
	{
		free(game->s_map.map);
		free(game->colors);
		free(game->paths);
		free(game->player->line);
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
}