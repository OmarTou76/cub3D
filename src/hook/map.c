/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:12:49 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/05 23:30:01 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	refresh_pixels_line(mlx_image_t *img_line)
{
	color_img(img_line, 0, img_line->width, img_line->height);
}

void	display_map(t_game *game)
{
	if (game->s_map.img_map->enabled)
	{
		game->s_map.img_map->enabled = false;
		game->player->img_player->enabled = false;
		game->player->line->img_line->enabled = false;
	}
	else
	{
		game->s_map.img_map->enabled = true;
		game->player->img_player->enabled = true;
		game->player->line->img_line->enabled = true;
	}
}
