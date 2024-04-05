/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:24:25 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/05 17:37:22 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	check_lines(char **m)
{
	int	x;
	int	y;

	y = 0;
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
				return (0);
			else if ((m[y][x] == ' ' && (m[y][x + 1] && m[y][x + 1] == '0')))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	check_columns(char **m)
{
	int	x;
	int	y;

	x = 0;
	while (m[0][x])
	{
		y = 0;
		while (m[y][x] == ' ')
			y++;
		if (m[y][x] != '1')
			return (0);
		while (m[y])
		{
			if ((!m[y + 1] || !m[y + 1][x] || m[y + 1][x] == ' ')
				&& m[y][x] == '0')
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
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				count++;
			if (count > 1)
				return (0);
			x++;
		}
		y++;
	}
	if (!count)
		return (0);
	return (1);
}

bool only_isspace(char *line)
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
		printf("ft_strlen(n->line) = %zu\n", ft_strlen(n->line));
		if (ft_strlen(n->line) && !only_isspace(n->line))
			return (free(map), 0);
		n = n->next;
	}
	if (!check_columns(map) || !check_lines(map) || !check_start_pos(map))
		return (free(map), 0);
	free(map);
	return (1);
}
