/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:13:08 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 22:22:25 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map_height_node(t_lines *node)
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

void	trim_end(char *line)
{
	int	i;

	i = ft_strlen(line);
	while (i > 0 && line[i - 1] == ' ')
		i--;
	line[i] = 0;
}

char	**node_to_map(t_lines **node)
{
	int		i;
	int		map_height;
	char	**map;

	map_height = get_map_height_node(*node);
	map = malloc((map_height + 1) * sizeof(char *));
	i = 0;
	while ((*node) && ft_strlen((*node)->line))
	{
		trim_end((*node)->line);
		map[i] = (*node)->line;
		i++;
		(*node) = (*node)->next;
	}
	map[i] = NULL;
	return (map);
}
