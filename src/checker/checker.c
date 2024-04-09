/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:23:42 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 14:23:45 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_map_height(t_lines *node)
{
	int		i;
	t_lines	*tmp;

	i = 0;
	tmp = node;
	while (tmp && ft_strlen(tmp->line))
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**node_to_map(t_lines **node)
{
	int		i;
	int		map_height;
	char	**map;

	map_height = get_map_height(*node);
	map = malloc((map_height + 1) * sizeof(char *));
	i = 0;
	while ((*node) && ft_strlen((*node)->line))
	{
		map[i] = (*node)->line;
		i++;
		(*node) = (*node)->next;
	}
	map[i] = NULL;
	return (map);
}

int	check_input(char const *progname, char const *filename, int argc)
{
	char	*ext;

	if (argc != 2)
	{
		ft_putstr_fd("Error\n[USAGE]: ", 2);
		ft_putstr_fd((char *)progname, 2);
		return (ft_putstr_fd(" <FILENAME>.cub .\n", 2), 0);
	}
	ext = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if (open(filename, O_RDONLY) == -1)
	{
		ft_putstr_fd("Error\n", 2);
		return (perror(filename), 0);
	}
	else
		close(open(filename, O_RDONLY));
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
