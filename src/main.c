/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:22:57 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/02 15:26:41 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char const *argv[])
{
	t_lines *node;
	t_game *game;

	if (!check_input(argv[0], argv[1], argc))
		return (1);
	node = save_data(argv[1]);
	if (!is_valid_data(node))
		return (free_nodes(node), 1);
	store_data(&game, node);
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!game->mlx)
		return (0);
	if (init_game(game))
	{
		mlx_key_hook(game->mlx, display_map, game);
		mlx_loop_hook(game->mlx, &hook_moves, game);
		mlx_loop(game->mlx);
	}
	free_nodes(node);
	delete_images(game);
	mlx_terminate(game->mlx);
	free_game(game);
	return (EXIT_SUCCESS);
}
