/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:22:57 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/11 01:01:15 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_hook(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if ((key.action == MLX_PRESS || key.action == MLX_REPEAT)
		&& key.key == MLX_KEY_H)
		display_map(game);
}

void	loop_hook(void *param)
{
	t_game	*game;
	int		prev_x;
	int		prev_y;
	float	prev_angle;

	game = (t_game *)param;
	prev_x = game->player->img_player->instances[0].x;
	prev_y = game->player->img_player->instances[0].y;
	prev_angle = game->player->angle;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		return (void)mlx_close_window(game->mlx);
	if (!game->animation.start && (mlx_is_mouse_down(game->mlx,
				MLX_MOUSE_BUTTON_LEFT) || mlx_is_key_down(game->mlx,
				MLX_KEY_F)))
		shoot(game);
	listen_mouse_event(game);
	shoot_animation(game);
	hook_moves(game);
	if (prev_x == game->player->img_player->instances[0].x
		&& game->player->img_player->instances[0].y == prev_y
		&& game->player->angle == prev_angle)
		return ;
	refresh_pixels_line(game->map.rays.img_line);
	raycast(game);
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
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!game->mlx)
		return (0);
	if (init_game(game))
	{
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
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
