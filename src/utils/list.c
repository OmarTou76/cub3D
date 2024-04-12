/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:27:15 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 19:27:22 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	radian_to_degree(float angle)
{
	return (angle * (180 / M_PI));
}

static void	save_line(t_lines **node, char *line)
{
	t_lines	*nw;
	t_lines	*tmp;

	nw = malloc(sizeof(t_lines));
	nw->line = ft_strdup(line);
	nw->next = NULL;
	if (nw->line[ft_strlen(nw->line) - 1] == '\n')
		nw->line[ft_strlen(nw->line) - 1] = 0;
	if (!*node)
		(*node) = nw;
	else
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = nw;
	}
}

t_lines	*save_data(char const *filename)
{
	int		fd;
	char	*line;
	t_lines	*node;

	node = NULL;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		save_line(&node, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (node);
}
