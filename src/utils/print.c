/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:18:57 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/19 20:46:03 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Prints detailed game settings including colors and textures to help with debugging.
 *
 * @param game Pointer to the game structure containing all game settings.
 */
void print_data(t_game *game)
{
    printf("\nCOLORS: \n\n");
    printf("\tFLOOR: %d - %d - %d\n", game->colors->floor[0],
           game->colors->floor[1], game->colors->floor[2]);
    printf("\tCEILING: %d - %d - %d\n", game->colors->ceiling[0],
           game->colors->ceiling[1], game->colors->ceiling[2]);

    printf("\nTEXTURES: \n\n");
    printf("\tNO: %s\n", game->paths->no);
    printf("\tEA: %s\n", game->paths->ea);
    printf("\tSO: %s\n", game->paths->so);
    printf("\tWE: %s\n", game->paths->we);

    printf("\nMAP:\n\n");
    int i = 0;
    while (game->s_map.map[i])
    {
        printf("\t%s\n", game->s_map.map[i]);
        i++;
    }
    printf("\n");
}

/**
 * Prints all lines stored in a linked list of t_lines structures.
 * Useful for debugging purposes to see the parsed data from a file.
 *
 * @param tmp Pointer to the head of the linked list of lines.
 */
void print_lines(t_lines *tmp)
{
    t_lines *node = tmp;
    while (node)
    {
        printf("[%s]\n", node->line);
        node = node->next;
    }
}
