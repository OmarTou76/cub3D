/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:19:31 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/19 21:35:33 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Frees all game-related memory allocations.
 * This function ensures that all dynamically allocated memory for the game
 * structure and its sub-components are properly freed.
 *
 * @param game Pointer to the game structure.
 */
void free_game(t_game *game)
{
    if (game != NULL)
    {
        free(game->s_map.map);   // Free the map array
        free(game->colors);      // Free the colors structure
        free(game->paths);       // Free the texture paths structure
        free(game);              // Finally, free the game structure itself
    }
}

/**
 * Frees a linked list of line nodes.
 * This function traverses a linked list of lines, freeing each line's content
 * and the line node itself.
 *
 * @param node Pointer to the head of the linked list of lines.
 */
void free_nodes(t_lines *node)
{
    t_lines *tmp;

    while (node)
    {
        tmp = node->next;
        free(node->line);  // Free the string within the node
        free(node);        // Free the node itself
        node = tmp;
    }
}

/**
 * Frees a linked list of vectors.
 * This function is responsible for freeing a linked list of vectors used to track
 * positions, ensuring no memory leaks occur from these structures.
 *
 * @param vecs Pointer to the head of the vector linked list.
 */
void free_vecs(t_vec *vecs)
{
    t_vec *tmp;

    while (vecs)
    {
        tmp = vecs->next;
        free(vecs);  // Free the vector node
        vecs = tmp;
    }
}
