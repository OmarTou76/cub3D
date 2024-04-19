/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:23:42 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/19 20:08:41 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Computes the number of non-empty lines in a linked list of lines,
 * which represents the parsed data from the map file.
 *
 * @param node Pointer to the head of the linked list of lines.
 * @return Number of non-empty lines.
 */
static int	get_map_height(t_lines *node)
{
	int		i;
	t_lines	*tmp;

	i = 0;
	tmp = node;
	while (tmp && tmp->line && ft_strlen(tmp->line))
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/**
 * Converts a linked list of lines into an array of strings.
 * Each line in the linked list becomes an entry in the array.
 *
 * @param node Address of the pointer to the head of the linked list.
 * @return Pointer to the array of strings or NULL if allocation fails.
 */
char	**node_to_map(t_lines **node)
{
	int		i;
	int		map_height;
	char	**map;

	map_height = get_map_height(*node);
	map = malloc((map_height + 1) * sizeof(char *));
	if (!map)
		return (NULL);
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

/**
 * Checks command-line arguments and verifies the existence and format of the input file.
 *
 * @param progname The name of the program (typically argv[0]).
 * @param filename The name of the file to be opened (typically argv[1]).
 * @param argc The number of command-line arguments.
 * @return 1 if all checks pass, 0 otherwise.
 */
int check_input(char const *progname, char const *filename, int argc) {
    if (argc != 2) {
        fprintf(stderr, "Error: Usage: %s <FILENAME>.cub\n", progname);
        return 0;
    }

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 0;
    }
    close(fd);

    char *ext = ft_strnstr(filename, ".cub", ft_strlen(filename));
    if (!ext || ft_strcmp(ext, ".cub") != 0) {
        fprintf(stderr, "Error: File must have a .cub extension\n");
        return 0;
    }
    return 1;
}

/**
 * Checks if a line can be the start of the map data.
 *
 * @param line The line to check.
 * @return 1 if the line consists only of '1' and space characters, 0 otherwise.
 */
int	is_map_start(char *line)
{
	int	i;

	i = 0;
	if (!ft_strlen(line))
		return (0);
	while (line[i] && (line[i] == '1' || line[i] == ' '))
		i++;
	return line[i] == '\0' ? 1 : 0;
}

/**
 * Validates the parsed data stored in a linked list against the map's rules and requirements.
 *
 * @param node Pointer to the head of the linked list of parsed lines.
 * @return 1 if data is valid, 0 otherwise, printing appropriate error messages.
 */
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
			break;
		if (ft_strlen(tmp->line) && !fields.is_ok && !is_map_start(tmp->line)
			&& !check_fields(tmp->line, &fields))
			return (ft_putstr_fd("Error\nInvalid fields input\n", 2), 0);
		tmp = tmp->next;
	}
	if (tmp && fields.is_ok && is_valid_map(&tmp))
		return 1;
	else if (!fields.is_ok)
		return (ft_putstr_fd("Error\nMissing params\n", 2), 0);
	else
		return (ft_putstr_fd("Error\nInvalid map\n", 2), 0);
}
