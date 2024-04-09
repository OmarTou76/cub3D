/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:19:31 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 19:27:15 by ymeziane         ###   ########.fr       */
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
