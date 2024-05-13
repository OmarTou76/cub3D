/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:23:42 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/13 13:43:29 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_fields(t_fields *f)
{
	f->c = 0;
	f->f = 0;
	f->no = 0;
	f->so = 0;
	f->ea = 0;
	f->we = 0;
	f->is_ok = 0;
}

int	check_input(char const *progname, char const *filename, int argc)
{
	char	*ext;
	int		fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error\n[USAGE]: ", 2);
		ft_putstr_fd((char *)progname, 2);
		return (ft_putstr_fd(" <FILENAME>.cub .\n", 2), 0);
	}
	ext = ft_strnstr(filename, ".cub", ft_strlen(filename));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		return (perror(filename), 0);
	}
	else
		close(fd);
	if (!ext || ft_strncmp(ext, ".cub", ft_strlen(ext)) != 0)
	{
		ft_putstr_fd("Error\n[USAGE]: ", 2);
		ft_putstr_fd((char *)progname, 2);
		return (ft_putstr_fd(" <FILENAME>.cub .\n", 2), 0);
	}
	return (1);
}

int	is_map_start(char *line)
{
	int	i;

	i = 0;
	if (!ft_strlen(line))
		return (0);
	while (line[i] && (line[i] == '1' || line[i] == ' '))
		i++;
	if (line[i])
		return (0);
	return (1);
}

int	is_valid_data(t_lines *node)
{
	t_lines		*tmp;
	t_fields	fields;

	tmp = node;
	if (!tmp)
		return (ft_putstr_fd("Error\nMap empty\n", 2), 0);
	init_fields(&fields);
	while (tmp)
	{
		if (ft_strlen(tmp->line) && fields.is_ok)
			break ;
		if (ft_strlen(tmp->line) && !fields.is_ok && !is_map_start(tmp->line)
			&& !check_fields(tmp->line, &fields))
			return (ft_putstr_fd("Error\nInvalid fields input\n", 2), 0);
		tmp = tmp->next;
	}
	if (tmp && fields.is_ok && is_valid_map(&tmp))
		return (1);
	else if (!fields.is_ok)
		return (ft_putstr_fd("Error\nMissing params\n", 2), 0);
	else
		return (ft_putstr_fd("Error\nInvalid map\n", 2), 0);
}
