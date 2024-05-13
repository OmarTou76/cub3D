/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:35:26 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/11 20:43:22 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_number(char *nb)
{
	int	i;

	i = 0;
	while (nb[i] && nb[i] == ' ')
		i++;
	while (nb[i] && (ft_isdigit(nb[i]) || (nb[i] == '+' || nb[i] == 'i')))
		i++;
	while (nb[i] && nb[i] == ' ')
		i++;
	if (nb[i] || (ft_atoi(nb) > 255 || ft_atoi(nb) < 0))
		return (0);
	return (1);
}

static int	char_occ(char *line, char set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == set)
			count++;
		i++;
	}
	return (count);
}

int	is_valid_rgb_data(char *line)
{
	char	**data;
	int		i;
	int		valid_data;

	i = 0;
	valid_data = 1;
	while (*line && (!ft_isdigit(*line) && !(*line == '+' || *line == '-')))
		line++;
	if (!*line || char_occ(line, ',') != 2)
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
