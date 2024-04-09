/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:24:02 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 14:28:29 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	has_vec(t_vec *vec, int y, int x)
{
	while (vec)
	{
		if (vec->y == y && vec->x == x)
			return (true);
		vec = vec->next;
	}
	return (false);
}

void	add_vec(t_vec **vecs, int y, int x)
{
	t_vec	*new;
	t_vec	*tmp;

	new = malloc(sizeof(t_vec));
	new->y = y;
	new->x = x;
	new->next = NULL;
	if (!*vecs)
		(*vecs) = new;
	else
	{
		tmp = *vecs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	is_valid_direction(char **m, int dy, int dx)
{
	if (m[dy] && m[dy][dx] && m[dy][dx] == '1')
		return (0);
	return (1);
}

void	fill_directions(int d[4][2])
{
	d[0][0] = -1;
	d[0][1] = 0;
	d[1][0] = 0;
	d[1][1] = 1;
	d[2][0] = 0;
	d[2][1] = -1;
	d[3][0] = 1;
	d[3][1] = 0;
}

int	is_spaces_outside(t_vec **vecs, char **m, int y, int x)
{
	int	i;
	int	dy;
	int	dx;
	int	directions[4][2];

	if (!m[y] || !m[y][x])
		return (1);
	if (m[y][x] == '0')
		return (0);
	fill_directions(directions);
	i = 0;
	add_vec(vecs, y, x);
	while (i < 4)
	{
		dy = y + directions[i][0];
		dx = x + directions[i][1];
		if (is_valid_direction(m, dy, dx) && !has_vec(*vecs, dy, dx))
			return (is_spaces_outside(vecs, m, dy, dx));
		i++;
	}
	return (0);
}
