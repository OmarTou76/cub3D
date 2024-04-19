/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:17:33 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/19 21:42:41 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Refreshes the player's movement deltas based on their current viewing angle.
 * This function converts the player's angle from degrees to radians and calculates
 * the components of movement in the x and y directions.
 *
 * @param g Pointer to the pointer of the game structure.
 */
static void refresh_deltas(t_game **g) {
    float angle_radians = (*g)->player->angle * M_PI / 180.0;
    float dx = PLAYER_SPEED * cos(-angle_radians);
    float dy = PLAYER_SPEED * sin(-angle_radians);

    (*g)->player->delta_x = (int)round(dx);
    (*g)->player->delta_y = (int)round(dy);
}



/**
 * Updates the player's position when moving left or right (strafing).
 *
 * @param key The keyboard data.
 * @param game Pointer to the game structure.
 * @param new_y Pointer to the new y-coordinate.
 * @param new_x Pointer to the new x-coordinate.
 */
static void update_left_and_right(mlx_key_data_t key, t_game *game, int *new_y, int *new_x) {
    if (key.key == MLX_KEY_A) {
        *new_x += PLAYER_SPEED * cos((game->player->angle * M_PI / 180.0) + M_PI / 2.0);
        *new_y -= PLAYER_SPEED * sin((game->player->angle * M_PI / 180.0) + M_PI / 2.0);
    } else if (key.key == MLX_KEY_D) {
        *new_x += PLAYER_SPEED * cos((game->player->angle * M_PI / 180.0) - M_PI / 2.0);
        *new_y -= PLAYER_SPEED * sin((game->player->angle * M_PI / 180.0) - M_PI / 2.0);
    }
}

/**
 * Processes movement based on user input and updates player's position accordingly.
 *
 * @param key The keyboard data.
 * @param game Pointer to the game structure.
 * @param new_y Initial y-coordinate for the movement calculation.
 * @param new_x Initial x-coordinate for the movement calculation.
 */
static void	check_and_moves(mlx_key_data_t key, t_game *game, int new_y,
		int new_x)
{
	if (key.key == MLX_KEY_W)
	{
		new_x += game->player->delta_x;
		new_y += game->player->delta_y;
	}
	else if (key.key == MLX_KEY_S)
	{
		new_x -= game->player->delta_x;
		new_y -= game->player->delta_y;
	}
	update_left_and_right(key, game, &new_y, &new_x);
	if ((game->s_map.map[new_y / (MAP_TILE_SIZE)][new_x
			/ (MAP_TILE_SIZE)] != '1') && game->s_map.map[(new_y + PLAYER_SIZE)
		/ (MAP_TILE_SIZE)][(new_x + PLAYER_SIZE) / (MAP_TILE_SIZE)] != '1')
	{
		game->player->img_player->instances[0].y = new_y;
		game->player->img_player->instances[0].x = new_x;
	}
}

/**
 * Rotates the player left or right and refreshes movement deltas.
 *
 * @param key The keyboard data.
 * @param game Pointer to the game structure.
 */
static void ft_turn_player(mlx_key_data_t key, t_game *game) {
    refresh_deltas(&game);
    if (key.key == MLX_KEY_RIGHT) {
        game->player->angle -= 5;
        if (game->player->angle < 0)
            game->player->angle += radian_to_degree(2 * M_PI);
    } else if (key.key == MLX_KEY_LEFT) {
        game->player->angle += 5;
        if (game->player->angle > radian_to_degree(2 * M_PI))
            game->player->angle -= radian_to_degree(2 * M_PI);
    } else {
        check_and_moves(key, game, game->player->img_player->instances[0].y, game->player->img_player->instances[0].x);
    }
}

/**
 * Toggles the visibility of the map, player, and line indicators.
 *
 * @param game Pointer to the game structure.
 */
void display_map(t_game *game) {
    if (!game->s_map.image_map->instances[0].enabled) {
        game->s_map.image_map->instances[0].enabled = true;
        game->player->img_player->instances[0].enabled = true;
        game->player->line->img_line[0].enabled = true;
    } else {
        game->s_map.image_map->instances[0].enabled = false;
        game->player->img_player->instances[0].enabled = false;
        game->player->line->img_line[0].enabled = false;
    }
}

/**
 * Handles keyboard input for player movement and map interaction.
 *
 * @param key The keyboard data.
 * @param param Additional parameter, used here to pass the game structure.
 */
void ft_move_player(mlx_key_data_t key, void *param) {
    t_game *game = (t_game *)param;
    if (key.action == MLX_PRESS || key.action == MLX_REPEAT) {
        if (key.key == MLX_KEY_ESCAPE)
            mlx_close_window(game->mlx);
        if (key.key == MLX_KEY_C)
            display_map(game);
        else if (key.key == MLX_KEY_W || key.key == MLX_KEY_S || key.key == MLX_KEY_A || key.key == MLX_KEY_D || key.key == MLX_KEY_LEFT || key.key == MLX_KEY_RIGHT)
            ft_turn_player(key, param);
        color_img(game->player->line->img_line, 0, game->player->line->img_line->width, game->player->line->img_line->height);
        for (int i = game->player->angle - 30; i < game->player->angle + 30; i++) {
            color_line(game->player->line->img_line, ft_pixel(255, 0, 0, 0xFF), game, i);
        }
    }
}