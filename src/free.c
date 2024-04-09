/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:19:31 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 14:25:23 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_game(t_game *game)
{
	if (game != NULL)
	{
		free(game->s_map.map);
		free(game->colors);
		free(game->paths);
		free(game);
	}
}
