/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:20:01 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/11 20:42:42 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	validate_initial_line_or_column(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (line[i] == '1');
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
		if (!validate_initial_line_or_column(m[y]))
			return (free_vecs(vecs), 0);
		x = 0;
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

int	check_columns(char **m)
{
	int	x;
	int	y;

	x = 0;
	while (m[0][x])
	{
		y = 0;
		if (!validate_initial_line_or_column(m[y]))
			return (0);
		while (m[y])
		{
			if ((!m[y + 1]
					|| (int)ft_strlen(m[y + 1]) <= x || m[y + 1][x] == ' ')
					&& ((int)ft_strlen(m[y]) > x && m[y][x] == '0'))
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
			if (count > 1 || !ft_strchr("NSWE10D ", c))
				return (0);
			x++;
		}
		y++;
	}
	if (!count)
		return (0);
	return (1);
}
