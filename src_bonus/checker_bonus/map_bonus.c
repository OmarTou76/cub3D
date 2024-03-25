/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:24:25 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 02:08:59 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	only_isspace(char *line)
{
	while (*line)
	{
		if (ft_isspace(*line) == 0)
			return (false);
		line++;
	}
	return (true);
}

int	is_valid_map(t_lines **node)
{
	char	**map;
	t_lines	*n;

	n = (*node);
	map = node_to_map(&n);
	while (n)
	{
		if (ft_strlen(n->line) && !only_isspace(n->line))
			return (free(map), 0);
		n = n->next;
	}
	if (!check_columns(map) || !check_lines(map) || !check_start_pos(map))
		return (free(map), 0);
	free(map);
	return (1);
}
