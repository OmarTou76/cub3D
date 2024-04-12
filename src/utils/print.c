/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:18:57 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 14:29:04 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_data(t_game *game)
{
	int	i;

	printf("\nCOLORS: \n\n");
	printf("\tFLOOR: %d - %d - %d\n", game->colors->floor[0],
		game->colors->floor[1], game->colors->floor[2]);
	printf("\tCEILING: %d - %d - %d\n", game->colors->ceiling[0],
		game->colors->ceiling[1], game->colors->ceiling[2]);
	printf("\nTEXTURES: \n\n");
	printf("\tNO: %s\n", game->paths->no);
	printf("\tEA: %s\n", game->paths->ea);
	printf("\tSO: %s\n", game->paths->so);
	printf("\tWE: %s\n", game->paths->we);
	printf("\n");
	printf("\nMAP:\n\n");
	i = 0;
	while (game->s_map.map[i])
	{
		printf("\t%s\n", game->s_map.map[i]);
		i++;
	}
	printf("\n");
}

void	print_lines(t_lines *tmp)
{
	t_lines	*node;

	node = tmp;
	while (node)
	{
		printf("[%s]\n", node->line);
		node = node->next;
	}
}
