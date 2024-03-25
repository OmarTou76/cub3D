/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:56:31 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 19:56:35 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_border_wall_index(t_wall *wall, float player_y, float player_x)
{
	if (player_y >= roundf(wall->collision_y) && player_x > wall->collision_x)
		return (0);
	else if (player_y < wall->collision_y && player_x > wall->collision_x)
		return (2);
	else if (player_y > wall->collision_y && player_x < wall->collision_x)
		return (3);
	else if (player_y < wall->collision_y && player_x < wall->collision_x)
		return (1);
	return (-1);
}

int	has_texture_conflict(float fract_y, float fract_x)
{
	return (((fract_y >= 0.99 && fract_x < 0.99) && (fract_x <= 0.01
				&& fract_y > 0.01)) || ((fract_y <= 0.01 && fract_x > 0.01)
			&& (fract_x >= 0.99 && fract_y < 0.99)) || (fract_x >= 0.99
			&& fract_y >= 0.99) || (fract_y <= 0.01 && fract_x <= 0.01));
}

void	save_wall_properties(t_game *game, t_wall *wall, t_ray_direction *ray)
{
	wall->distance = (sqrt(pow(ray->end_x - ray->start_x, 2) + pow(ray->end_y
					- ray->start_y, 2)));
	ray->normalize_dist = (game->player->angle * M_PI / 180)
		- (wall->column_angle * M_PI / 180);
	wall->height = (game->img_view_3d->height / (wall->distance
				* cos(ray->normalize_dist))) * (game->map.tile_size);
}
