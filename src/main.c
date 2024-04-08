/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:22:57 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/08 17:19:04 by ymeziane         ###   ########.fr       */
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
	while (game->s_map.map[i])
	{
		printf("\t%s\n", game->s_map.map[i]);
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

static void free_game(t_game *game) {
    if (game != NULL)
	{
        free(game->s_map.map);
        free(game->colors);
        free(game->paths);
        free(game);
    }
}



void	ft_moove_player(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key.action == MLX_PRESS)
	{
		if (key.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		if (key.key == MLX_KEY_UP)
			game->img_player->instances[0].y -= TILE_SIZE;
		if (key.key == MLX_KEY_DOWN)
			game->img_player->instances[0].y += TILE_SIZE;
		if (key.key == MLX_KEY_LEFT)
			game->img_player->instances[0].x -= TILE_SIZE;
		if (key.key == MLX_KEY_RIGHT)
			game->img_player->instances[0].x += TILE_SIZE;
	}
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
	store_data(&game, node);
	printf("game->s_map.width = %d\n", game->s_map.width);
	printf("game->s_map.height = %d\n", game->s_map.height);
	printf("game->s_map.player.x = %d\n", game->s_map.player.x);
	printf("game->s_map.player.y = %d\n", game->s_map.player.y);
	game->mlx = mlx_init(game->s_map.width * TILE_SIZE, game->s_map.height
			* TILE_SIZE, "cub3D", true);
	if (!game->mlx)
		return (0);
	draw_map_2D(game);
	mlx_key_hook(game->mlx, ft_moove_player, game);
	mlx_loop(game->mlx);
	print_lines(node);
	print_data(game);
	free_nodes(node);
	mlx_terminate(game->mlx);
	free_game(game);
	return (EXIT_SUCCESS);
}
