/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:58:39 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 13:35:12 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	store_data(t_game **game, t_lines *node)
{
	t_lines	*tmp;

	tmp = node;
	(*game) = malloc(sizeof(t_game));
	(*game)->paths = malloc(sizeof(t_texture_paths));
	(*game)->colors = malloc(sizeof(t_colors));
	while (tmp)
	{
		get_textures_paths(game, tmp->line);
		get_colors(game, tmp->line);
		if (ft_strlen(tmp->line) && is_map_start(tmp->line))
		{
			(*game)->map.map = node_to_map(&tmp);
			break ;
		}
		tmp = tmp->next;
	}
	(*game)->player = get_info_player((*game)->map.map);
	(*game)->animation.start = false;
	(*game)->mouse_event = true;
	store_map_data(game);
}
