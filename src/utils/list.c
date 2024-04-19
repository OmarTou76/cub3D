/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:27:15 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/19 21:05:06 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Converts an angle in radians to degrees.
 *
 * @param angle Angle in radians.
 * @return Angle in degrees.
 */
float radian_to_degree(float angle)
{
    return (angle * (180 / M_PI));
}

/**
 * Saves a line to a linked list of t_lines. This function appends a new node
 * with the given line to the end of the list.
 *
 * @param node Pointer to the head of the list.
 * @param line String to save in the list.
 */
static int save_line(t_lines **node, char *line)
{
    t_lines *nw;
    t_lines *tmp;

    nw = malloc(sizeof(t_lines));
    if (!nw)
        return (0);
    nw->line = ft_strdup(line);
    nw->next = NULL;
    if (nw->line && nw->line[ft_strlen(nw->line) - 1] == '\n')
        nw->line[ft_strlen(nw->line) - 1] = 0; // Remove newline at the end of the line

    if (!*node) // If the list is empty, start a new list
        (*node) = nw;
    else // Otherwise, append to the end of the list
    {
        tmp = *node;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = nw;
    }
	return (1);
}

/**
 * Reads lines from a file and saves them in a linked list. Each line from the file
 * is stored in a separate node in the list.
 *
 * @param filename Path to the file to read.
 * @return Pointer to the head of the linked list containing the file's lines.
 */
t_lines *save_data(char const *filename)
{
    int fd;
    char *line;
    t_lines *node;

    node = NULL;
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return NULL;
    }

    line = get_next_line(fd);
    while (line)
    {
        if(!save_line(&node, line))
			return (free(line), NULL);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return node;
}
