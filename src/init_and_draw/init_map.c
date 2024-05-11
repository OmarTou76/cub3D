/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:13:08 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/11 20:14:16 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_map_height(t_lines *node)
{
	int		i;
	t_lines	*tmp;

	i = 0;
	tmp = node;
	while (tmp && ft_strlen(tmp->line))
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**node_to_map(t_lines **node)
{
	int		i;
	int		map_height;
	char	**map;

	map_height = get_map_height(*node);
	map = malloc((map_height + 1) * sizeof(char *));
	i = 0;
	while ((*node) && ft_strlen((*node)->line))
	{
		map[i] = (*node)->line;
		i++;
		(*node) = (*node)->next;
	}
	map[i] = NULL;
	return (map);
}