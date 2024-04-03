/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:22:57 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/03 21:59:55 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	print_data(t_game *game)
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
	while (game->map[i])
	{
		printf("\t%s\n", game->map[i]);
		i++;
	}
	printf("\n");
}

static void	print_lines(t_lines *tmp)
{
	t_lines	*node;

	node = tmp;
	while (node)
	{
		printf("[%s]\n", node->line);
		node = node->next;
	}
}

static void	free_game(t_game *game)
{
	free(game->colors);
	free(game->paths);
	free(game->map);
	free(game);
}

int	main(int argc, char const *argv[])
{
	t_lines	*node;
	t_game	*game;

	if (!check_input(argv[0], argv[1], argc))
		return (1);
	node = save_data(argv[1]);
	if (!is_valid_data(node))
		return (free_nodes(node), 1);
	print_lines(node);
	store_data(&game, node);
	print_data(game);
	free_nodes(node);
	free_game(game);
}
