/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:23:08 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 13:51:26 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_extension(char *path)
{
	char	*ext;

	ext = path + ft_strlen(path) - 4;
	if (!ext || ft_strncmp(ext, ".png", ft_strlen(ext)) != 0)
		return (0);
	return (1);
}

static bool	valid_texture_path(char *line)
{
	int	i;
	int	fd;

	i = 0;
	while (*line && *line == ' ')
		line++;
	line += 3;
	while (*line && *line == ' ')
		line++;
	if (!(*line))
		return (0);
	while (line[i] && line[i] != ' ')
		i++;
	line[i] = '\0';
	fd = open(line, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	if (!check_extension(line))
		return (0);
	return (1);
}

int	trim_compare(char *base, char *to_compare, size_t size)
{
	while (*base && *base == ' ')
		base++;
	return (ft_strncmp(base, to_compare, size));
}

int	check_fields(char *line, t_fields *fields)
{
	if (trim_compare(line, "NO ", 3) == 0 && valid_texture_path(line))
		fields->no++;
	else if (trim_compare(line, "EA ", 3) == 0 && valid_texture_path(line))
		fields->ea++;
	else if (trim_compare(line, "SO ", 3) == 0 && valid_texture_path(line))
		fields->so++;
	else if (trim_compare(line, "WE ", 3) == 0 && valid_texture_path(line))
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
