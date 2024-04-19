/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:53:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/19 21:20:10 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Initializes and draws the player on the map.
 *
 * @param game Pointer to the game structure containing all game-related data.
 */
void init_and_draw_player(t_game *game)
{
    uint32_t color = ft_pixel(0, 255, 0, 0xFF);  // Set player color to green
    game->player->img_player = mlx_new_image(game->mlx, PLAYER_SIZE, PLAYER_SIZE);
    if (!game->player->img_player || 
        (mlx_image_to_window(game->mlx, game->player->img_player, 
        game->player->pos.x * MAP_TILE_SIZE + MAP_TILE_SIZE / 2 - PLAYER_SIZE / 2, 
        game->player->pos.y * MAP_TILE_SIZE + MAP_TILE_SIZE / 2 - PLAYER_SIZE / 2) == -1)) {
        printf("Error\n");
        return;
    }
    color_img(game->player->img_player, color, PLAYER_SIZE, PLAYER_SIZE);
    game->player->img_player->instances[0].z = 3;
    game->player->img_player->instances[0].enabled = false;  // Initially disable player visibility
}

/**
 * Initializes the directional line data used for player movement visualization.
 *
 * @param line Pointer to the directional line structure.
 * @param angle The viewing angle of the line.
 * @param line_height The height of the line.
 */
void initialize_line_data(t_direction_line *line, double angle, unsigned int line_height)
{
    float angle_radians = angle * M_PI / 180.0;
    line->start_x = line_height;
    line->start_y = line_height;
    line->end_x = line->start_x + line_height * cos(angle_radians);
    line->end_y = line->start_y - line_height * sin(angle_radians);
    line->delta_x = abs(line->end_x - line->start_x);
    line->delta_y = abs(line->end_y - line->start_y);
    line->step_x = line->start_x < line->end_x ? 1 : -1;
    line->step_y = line->start_y < line->end_y ? 1 : -1;
    line->error = line->delta_x - line->delta_y;
}

/**
 * Converts RGBA color format to ARGB.
 *
 * @param rgba Color value in RGBA format.
 * @return Color value in ARGB format.
 */
uint32_t convert_rgba_to_argb(uint32_t rgba)
{
    uint8_t red = (rgba >> 24) & 0xFF;
    uint8_t green = (rgba >> 16) & 0xFF;
    uint8_t blue = (rgba >> 8) & 0xFF;
    uint8_t alpha = rgba & 0xFF;
    return ((alpha << 24) | (blue << 16) | (green << 8) | red);
}

/**
 * Draws a column on the screen to represent a 3D wall slice.
 *
 * @param game Pointer to the game structure.
 * @param angle The angle of the column in relation to the player's view.
 * @param wall_height The calculated height of the wall slice based on distance.
 */
void draw_3d_col(t_game *game, double angle, float wall_height)
{
    double min = game->player->angle - 30;
    int index = 59;
    while (min != angle) {
        min++;
        index--;
    }
    int width = game->img_view_3d->width / 59;
    float texture_x = (float)(index % game->wall_image->width);
    int offset = ((game->s_map.height / 2) - (wall_height / 2)) * TILE_SIZE;
    for (int y = 0; y < (int)game->img_view_3d->height; y++) {
        int x = (index * width);
        while (x < (index * width) + width) {
            if (y >= offset && y < offset + wall_height * TILE_SIZE) {
                int texture_y = ((float)(y - offset) / (wall_height * TILE_SIZE)) * game->wall_image->height;
                if (texture_y >= (int)game->wall_image->height)
                    texture_y = game->wall_image->height - 1;
                uint32_t rgba_color = ((uint32_t *)game->wall_image->pixels)[texture_y * game->wall_image->width + (int)texture_x];
                uint32_t argb_color = convert_rgba_to_argb(rgba_color);
                mlx_put_pixel(game->img_view_3d, x, y, argb_color);
            } else if (y < offset) {
                mlx_put_pixel(game->img_view_3d, x, y, ft_pixel(game->colors->ceiling[0], game->colors->ceiling[1], game->colors->ceiling[2], 0xFF));
            } else {
                mlx_put_pixel(game->img_view_3d, x, y, ft_pixel(game->colors->floor[0], game->colors->floor[1], game->colors->floor[2], 0xFF));
            }
            x++;
        }
    }
}

/**
 * Initializes the line length based on the maximum dimension of the display window.
 *
 * @param game Pointer to the game structure.
 */
void init_line_length(t_game *game)
{
    game->player->line->length = (game->mlx->height > game->mlx->width) ? game->mlx->height : game->mlx->width;
}

/**
 * Initializes and draws directional lines around the player to indicate viewing directions.
 *
 * @param game Pointer to the game structure.
 */
void init_and_draw_lines(t_game *game)
{
	init_line_length(game);
    uint32_t color = ft_pixel(255, 0, 0, 0xFF);  // Red color for direction lines
    game->player->line->img_line = mlx_new_image(game->mlx, game->player->line->length * 2, game->player->line->length * 2);
    if (!game->player->line->img_line || (mlx_image_to_window(game->mlx, game->player->line->img_line, 0, 0) == -1)) {
        printf("Error\n");
        return;
    }
    double i = game->player->angle - 30;
    while (i < game->player->angle + 30) {
        color_line(game->player->line->img_line, color, game, i);
        i++;
    }
    game->player->line->img_line->instances[0].z = 2;
	game->player->line->img_line[0].enabled = false;  // Initially disable line visibility
}

/**
 * Sets the depth for an image in the display window.
 *
 * @param img Pointer to the image structure.
 * @param z Depth value.
 */
void set_depth_img(mlx_image_t *img, int z)
{
    unsigned int x = 0;
    while (img->instances[x].z) {
        img->instances[x].z = z;
        x++;
    }
}

/**
 * Fills a specified region of an image with a given color.
 *
 * @param img Pointer to the image structure.
 * @param posY Y-coordinate of the top-left corner of the region to fill.
 * @param posX X-coordinate of the top-left corner of the region to fill.
 * @param color Color to fill the region with.
 */
void fill_by_pixel(mlx_image_t *img, int posY, int posX, int32_t color)
{
    int y = posY + 1;
    while (y < posY + MAP_TILE_SIZE) {
        int x = posX + 1;
        while (x < posX + MAP_TILE_SIZE) {
            mlx_put_pixel(img, x, y, color);
            x++;
        }
        y++;
    }
}

/**
 * Initializes and draws the 2D map for the game.
 *
 * @param game Pointer to the game structure.
 */
void init_and_draw_map(t_game *game)
{
    game->s_map.image_map = mlx_new_image(game->mlx, game->s_map.width * MAP_TILE_SIZE, game->s_map.height * MAP_TILE_SIZE);
    unsigned int y = 0;
    while (y < game->s_map.height) {
        unsigned int x = 0;
        while (x < game->s_map.width && ft_strlen(game->s_map.map[y]) > x) {
            if (game->s_map.map[y][x] == '1') {
                fill_by_pixel(game->s_map.image_map, (y * MAP_TILE_SIZE), (x * MAP_TILE_SIZE), ft_pixel(0, 0, 0, 0xFF));
            }
            x++;
        }
        y++;
    }
    mlx_image_to_window(game->mlx, game->s_map.image_map, 0, 0);
    game->s_map.image_map->instances[0].z = 3;
    game->s_map.image_map->instances[0].enabled = false;
}

/**
 * Draws the entire 2D map, including player and directional lines.
 *
 * @param game Pointer to the game structure.
 */
void draw_map2d(t_game *game)
{
    init_and_draw_player(game);
    init_and_draw_lines(game);
    init_and_draw_map(game);
}
