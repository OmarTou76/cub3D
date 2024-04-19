/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:24:25 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/19 20:58:58 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Validates that all lines in the map start with a '1' and checks for isolated zeroes.
 *
 * @param m Array of strings representing the map.
 * @return 1 if all lines are valid, 0 otherwise.
 */
static int check_lines(char **m)
{
    int x, y;
    t_vec *vecs;

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

/**
 * Validates that all columns in the map start with a '1' and checks for isolated zeroes.
 *
 * @param m Array of strings representing the map.
 * @return 1 if all columns are valid, 0 otherwise.
 */
static int check_columns(char **m)
{
    int x, y;

    x = 0;
    while (m[0][x])
    {
        y = 0;
        while (m[y][x] && m[y][x] == ' ')
            y++;
        if (m[y][x] != '1')
            return (0);
        while (m[y])
        {
            if ((!m[y + 1] || (int)ft_strlen(m[y + 1]) <= x || m[y + 1][x] == ' ') && ((int)ft_strlen(m[y]) > x && m[y][x] == '0'))
                return (0);
            y++;
        }
        x++;
    }
    return (1);
}

/**
 * Checks for a valid start position on the map. Ensures there is exactly one start position.
 *
 * @param map Array of strings representing the map.
 * @return 1 if exactly one valid start position is found, 0 otherwise.
 */
static int check_start_pos(char **map)
{
    int y, x, count;
    char c;

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

/**
 * Checks if a line contains only whitespace.
 *
 * @param line String to check.
 * @return true if only whitespace is found, false otherwise.
 */
bool only_isspace(char *line)
{
    while (*line)
    {
        if (ft_isspace(*line) == 0)
            return false;
        line++;
    }
    return true;
}

/**
 * Validates the entire map for the game, including checks for structure, isolated zeroes, and start position.
 *
 * @param node Address of pointer to the head of the linked list of lines.
 * @return 1 if the map is valid, 0 otherwise.
 */
int is_valid_map(t_lines **node)
{
    char **map;
    t_lines *n;

    n = (*node);
    map = node_to_map(&n);
    if (!map)
        return (0);
    while (n)
    {
        if (ft_strlen(n->line) && !only_isspace(n->line))
            return (free(map), 0);
        n = n->next;
    }
    if (!check_columns(map) || !check_lines(map) || !check_start_pos(map))
        return (free(map), 0);
    free(map);
    return (1);
}
