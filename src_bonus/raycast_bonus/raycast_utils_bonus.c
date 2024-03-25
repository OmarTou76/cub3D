/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:27:07 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 20:02:35 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_cracked_wall(t_wall *wall, t_game *game, int texture_index)
{
	if ((texture_index == 1 || texture_index == 3)
		&& game->map.map[(int)(wall->collision_y)]
		[(int)floor(wall->collision_x)] == 'D')
		return (true);
	else if ((texture_index == 0 || texture_index == 2)
		&& game->map.map[(int)floor(wall->collision_y)]
		[(int)(wall->collision_x)] == 'D')
		return (true);
	return (false);
}

void	init_ray_properties(t_ray_direction *ray, t_game *game, t_wall *wall)
{
	ray->start_x = game->player->img_player->instances[0].x
		+ game->player->img_player->width / 2;
	ray->start_y = game->player->img_player->instances[0].y
		+ game->player->img_player->height / 2;
	ray->end_x = ray->start_x;
	ray->end_y = ray->start_y;
	ray->angle_radian = wall->column_angle * M_PI / 180;
	ray->step_y = sin(-ray->angle_radian) * 0.2;
	ray->step_x = cos(-ray->angle_radian) * 0.2;
}
