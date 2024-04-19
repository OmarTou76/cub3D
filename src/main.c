/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:22:57 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/19 20:13:23 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char const *argv[])
{
	t_lines	*node; // Structure for storing the parsed file data
	t_game	*game; // Main game structure holding all game-related data

	if (!check_input(argv[0], argv[1], argc)) // Check command line arguments
		return (1);

	node = save_data(argv[1]); // Parse the .cub file and save the data
	if(!node)
		return (1);
	if (!is_valid_data(node)) // Validate the parsed data
		return (free_nodes(node), 1);

	if(!store_data(&game, node)) // Store the validated data into the game structure
		return (free_nodes(node), 1); 

	game->mlx = mlx_init((game->s_map.width * TILE_SIZE), game->s_map.height
			* TILE_SIZE, "cub3D", true); // Initialize the MLX graphics library
	if (!game->mlx)
		return (0);

	draw_map2d(game); // Draw the 2D map representation
	mlx_key_hook(game->mlx, ft_move_player, game); // Set up keyboard input handling
	mlx_loop(game->mlx); // Start the MLX event loop

	free_nodes(node); // Free the linked list of parsed data
	mlx_terminate(game->mlx); // Properly shutdown MLX
	free_game(game); // Free all allocated game resources

	return (EXIT_SUCCESS);
}
