/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:27:07 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 14:48:29 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
