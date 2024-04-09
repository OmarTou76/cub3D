/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:22:57 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 14:27:02 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char const *argv[])
{
	t_lines	*node;
	t_game	*game;

	if (!check_input(argv[0], argv[1], argc))
		return (1);
	node = save_data(argv[1]);
	if (!is_valid_data(node))
		return (free_nodes(node), 1);
	store_data(&game, node);
	printf("game->s_map.width = %d\n", game->s_map.width);
	printf("game->s_map.height = %d\n", game->s_map.height);
	printf("game->player->pos.x = %d\n", game->player->pos.x);
	printf("game->player->pos.y = %d\n", game->player->pos.y);
	game->mlx = mlx_init(game->s_map.width * TILE_SIZE, game->s_map.height
			* TILE_SIZE, "cub3D", true);
	if (!game->mlx)
		return (0);
	draw_map2d(game);
	mlx_key_hook(game->mlx, ft_moove_player, game);
	mlx_loop(game->mlx);
	print_lines(node);
	print_data(game);
	free_nodes(node);
	mlx_terminate(game->mlx);
	free_game(game);
	return (EXIT_SUCCESS);
}
