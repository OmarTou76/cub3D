/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otourabi <otourabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:22:57 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/18 13:06:53 by otourabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char const *argv[])
{
	t_lines			*node;
	t_game			*game;
	mlx_texture_t	*wall_texture;

	if (!check_input(argv[0], argv[1], argc))
		return (1);
	node = save_data(argv[1]);
	if (!is_valid_data(node))
		return (free_nodes(node), 1);
	store_data(&game, node);
	game->mlx = mlx_init((game->s_map.width * TILE_SIZE), game->s_map.height
			* TILE_SIZE, "cub3D", true);
	if (!game->mlx)
		return (0);
	wall_texture = mlx_load_png("textures/our/plank.png");
	game->wall_image = mlx_texture_to_image(game->mlx, wall_texture);
	mlx_resize_image(game->wall_image, 64, 64);
	// mlx_image_to_window(game->mlx, game->wall_image, 0, 0);
	draw_map2d(game);
	mlx_key_hook(game->mlx, ft_moove_player, game);
	mlx_loop(game->mlx);
	// print_lines(node);
	// print_data(game);
	free_nodes(node);
	mlx_terminate(game->mlx);
	free_game(game);
	return (EXIT_SUCCESS);
}
