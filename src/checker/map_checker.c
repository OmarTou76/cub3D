/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:24:25 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/08 16:54:59 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	check_lines(char **m)
{
	int		x;
	int		y;
	t_vec	*vecs;

	y = 0;
	vecs = NULL;
	while (m[y])
	{
		x = 0;
		while (m[y][x] && m[y][x] == ' ')
			x++;
		if (m[y][x] != '1')
			return (0);
		while (m[y][x])
		{
			if ((!m[y][x + 1] || m[y][x + 1] == ' ') && m[y][x] == '0')
				return (free_vecs(vecs), 0);
			else if ((m[y][x] == ' ' && (m[y][x + 1] && m[y][x + 1] == '0')))
				return (free_vecs(vecs), 0);
			else if (m[y][x] == ' ' && !has_vec(vecs, y, x)
				&& !is_spaces_outside(&vecs, m, y, x))
				return (free_vecs(vecs), 0);
			x++;
		}
		y++;
	}
	return (free_vecs(vecs), 1);
}

static int	check_columns(char **m)
{
	int	x;
	int	y;

	x = 0;
	while (m[0][x])
	{
		y = 0;
		while (m[y][x] && m[y][x] == ' ')
			y++;
		if (m[y][x] != '1')
			return (0);
		while (m[y])
		{
			if ((!m[y + 1] || (int)ft_strlen(m[y + 1]) <= x || m[y + 1][x] == ' ')
				&& ((int)ft_strlen(m[y]) > x && m[y][x] == '0'))
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

static int	check_start_pos(char **map)
{
	int		y;
	int		x;
	int		count;
	char	c;

	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (ft_strchr("NSWE", c))
				count++;
			if (count > 1 || !ft_strchr("NSWE10 ", c))
				return (0);
			x++;
		}
		y++;
	}
	if (!count)
		return (0);
	return (1);
}

bool	only_isspace(char *line)
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
