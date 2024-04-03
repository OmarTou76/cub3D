/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:23:08 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/03 22:02:00 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_fields(t_fields *f)
{
	f->c = 0;
	f->f = 0;
	f->no = 0;
	f->so = 0;
	f->ea = 0;
	f->we = 0;
	f->is_ok = 0;
}

int	trim_compare(char *base, char *to_compare, size_t size)
{
	while (*base && *base == ' ')
		base++;
	return (ft_strncmp(base, to_compare, size));
}

static int	is_valid_number(char *nb)
{
	int	i;

	i = 0;
	while (nb[i] && nb[i] == ' ')
		i++;
	while (nb[i] && ft_isdigit(nb[i]))
		i++;
	if (nb[i] || (ft_atoi(nb) > 255 || ft_atoi(nb) < 0))
		return (0);
	return (1);
}

static int	is_valid_rgb_data(char *line)
{
	char	**data;
	int		i;
	int		valid_data;

	i = 0;
	valid_data = 1;
	while (*line && !ft_isdigit(*line))
		line++;
	if (!*line)
		return (0);
	data = ft_split(line, ',');
	while (data[i])
	{
		if (!is_valid_number(data[i]))
			valid_data = 0;
		free(data[i]);
		i++;
	}
	if (i != 3)
		valid_data = 0;
	free(data);
	return (valid_data);
}

int	check_fields(char *line, t_fields *fields)
{
	if (trim_compare(line, "NO ", 3) == 0)
		fields->no++;
	else if (trim_compare(line, "EA ", 3) == 0)
		fields->ea++;
	else if (trim_compare(line, "SO ", 3) == 0)
		fields->so++;
	else if (trim_compare(line, "WE ", 3) == 0)
		fields->we++;
	else if (trim_compare(line, "C ", 2) == 0 && is_valid_rgb_data(line))
		fields->c++;
	else if (trim_compare(line, "F ", 2) == 0 && is_valid_rgb_data(line))
		fields->f++;
	else
		return (0);
	if (fields->no == 1 && fields->ea == 1 && fields->so == 1 && fields->we == 1
		&& fields->c == 1 && fields->f == 1)
		fields->is_ok = 1;
	else
		fields->is_ok = 0;
	return (1);
}
