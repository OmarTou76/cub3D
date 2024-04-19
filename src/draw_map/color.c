/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:56:00 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/19 21:33:22 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Constructs a pixel value from separate red, green, blue, and alpha components.
 * 
 * @param r Red component of the color.
 * @param g Green component of the color.
 * @param b Blue component of the color.
 * @param a Alpha component of the color (transparency).
 * @return A 32-bit integer representing the pixel color in RGBA format.
 */
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * Colors an entire image with a single color.
 *
 * @param img Pointer to the image structure.
 * @param color Color to fill the image with.
 * @param width Width of the area to color.
 * @param height Height of the area to color.
 */
void	color_img(mlx_image_t *img, uint32_t color, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel(img, x, y, color); // Set each pixel to the specified color
			x++;
		}
		y++;
	}
}


/**
 * Initializes line data and configures its position relative to the player's position.
 *
 * @param line Pointer to the line data structure.
 * @param img Pointer to the image where the line will be drawn.
 * @param game Pointer to the game structure for accessing global game data.
 * @param angle The angle of the line in degrees.
 */
static void	initialize_line(t_direction_line *line, mlx_image_t *img,
		t_game *game, double angle)
{
	// Set line's initial position relative to the player
	img->instances[0].x = game->player->img_player->instances[0].x
		- line->length + game->player->img_player->width / 2;
	img->instances[0].y = game->player->img_player->instances[0].y
		- line->length + game->player->img_player->height / 2;
	initialize_line_data(line, angle, line->length);
}

/**
 * Updates the position of a line during drawing, handling step and error calculation.
 *
 * @param line Pointer to the line data structure to be updated.
 */
static void	update_line_position(t_direction_line *line)
{
	line->error2 = line->error * 2;
	if (line->error2 > -line->delta_y)
	{
		line->error -= line->delta_y;
		line->start_x += line->step_x;
	}
	if (line->error2 < line->delta_x)
	{
		line->error += line->delta_x;
		line->start_y += line->step_y;
	}
}

/**
 * Processes line drawing, checking map boundaries and obstacles.
 *
 * @param img Pointer to the image where the line is drawn.
 * @param game Pointer to the game structure.
 * @param color The color of the line.
 * @param angle The angle of the line in degrees.
 * @return 1 if the line was drawn without hitting an obstacle, 0 otherwise.
 */
static int process_line_drawing(mlx_image_t *img, t_game *game, uint32_t color,
                                double angle) {
    unsigned int x, y;
	(void)angle;
    while (true) {
        y = (img->instances[0].y + game->player->line->start_y) / (MAP_TILE_SIZE);
        x = (img->instances[0].x + game->player->line->start_x) / (MAP_TILE_SIZE);

        if (x >= game->s_map.width || y >= game->s_map.height)
            break;

        if (game->s_map.map[y][x] == '1') {
            return (0);
        }

        if (game->player->line->start_x < 0 || game->player->line->start_x >= (int)img->width ||
            game->player->line->start_y < 0 || game->player->line->start_y >= (int)img->height)
            break;

        mlx_put_pixel(img, game->player->line->start_x, game->player->line->start_y, color);
        update_line_position(game->player->line);
    }
    return (1);
}


/**
 * Initializes and processes the drawing of a line.
 *
 * @param img Pointer to the image where the line will be drawn.
 * @param color Color of the line.
 * @param game Pointer to the game structure.
 * @param angle Angle of the line in degrees.
 */
void	color_line(mlx_image_t *img, uint32_t color, t_game *game, double angle)
{
	initialize_line(game->player->line, img, game, angle);
	if (!process_line_drawing(img, game, color, angle))
		return ;
}
