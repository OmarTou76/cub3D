/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:41:08 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/11 19:28:45 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

uint32_t	convert_rgba_to_argb(uint32_t rgba)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;

	red = (rgba >> 24) & 0xFF;
	green = (rgba >> 16) & 0xFF;
	blue = (rgba >> 8) & 0xFF;
	alpha = rgba & 0xFF;
	return ((alpha << 24) | (blue << 16) | (green << 8) | red);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

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
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
