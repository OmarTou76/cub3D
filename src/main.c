/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:22:57 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/06 08:42:09 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void key_hook(mlx_key_data_t key, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if ((key.action == MLX_PRESS || key.action == MLX_REPEAT) && key.key == MLX_KEY_H)
		display_map(game);
	if (key.action == MLX_PRESS && key.key == MLX_KEY_F)
		shoot(game);
}

void loop_hook(void *param)
{
	t_game *game = (t_game *)param;
	if(mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
		shoot(game);
	listen_mouse_event(game);
	shoot_animation(game);
	hook_moves(game);
}

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
		mlx_key_hook(game->mlx, key_hook, game);
		mlx_loop_hook(game->mlx, &loop_hook, game);
		mlx_loop(game->mlx);
	}
	free_nodes(node);
	delete_images(game);
	mlx_terminate(game->mlx);
	free_game(game);
	return (EXIT_SUCCESS);
}
