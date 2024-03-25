/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:20:01 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 18:22:02 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	check_neighbors(char **m, int y, int x, t_vec **vecs)
{
	if ((!m[y][x + 1] || m[y][x + 1] == ' ') && m[y][x] == '0')
		return (false);
	else if ((m[y][x] == ' ' && (m[y][x + 1] && m[y][x + 1] == '0')))
		return (false);
	else if (m[y][x] == ' ' && !has_vec(*vecs, y, x) && !is_spaces_outside(vecs,
			m, y, x))
		return (false);
	else if (x == (int)ft_strlen(m[y]) - 1 && m[y][x] != '1')
		return (false);
	return (true);
}

int	check_lines(char **m)
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
			if (!check_neighbors(m, y, x, &vecs))
				return (free_vecs(vecs), 0);
			x++;
		}
		y++;
	}
	return (free_vecs(vecs), 1);
}

int	check_columns(char **m)
{
	int	x;
	int	y;
	int	max;

	x = 0;
	max = get_max_width(m);
	while (x < max)
	{
		y = 0;
		while (m[y][x] && m[y][x] == ' ')
			y++;
		if (m[y][x] && m[y][x] != '1')
			return (0);
		while (m[y])
		{
			if ((!m[y + 1] || (int)ft_strlen(m[y + 1]) <= x || m[y
						+ 1][x] == ' ') && ((int)ft_strlen(m[y]) > x
						&& m[y][x] == '0'))
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int	check_start_pos(char **map)
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
