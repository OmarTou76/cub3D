/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:24:02 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/19 21:02:33 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#include "cub3D.h"

/**
 * Checks if a vector with specified coordinates exists in the list.
 *
 * @param vec Pointer to the start of the vector list.
 * @param y The y-coordinate to check.
 * @param x The x-coordinate to check.
 * @return true if the vector is found, false otherwise.
 */
bool has_vec(t_vec *vec, int y, int x)
{
    while (vec)
    {
        if (vec->y == y && vec->x == x)
            return true;
        vec = vec->next;
    }
    return false;
}

/**
 * Adds a new vector with specified coordinates to the list.
 *
 * @param vecs Pointer to the pointer to the start of the vector list.
 * @param y The y-coordinate of the new vector.
 * @param x The x-coordinate of the new vector.
 */
void add_vec(t_vec **vecs, int y, int x)
{
    t_vec *new = malloc(sizeof(t_vec));
    if (!new)
        return; // Handle memory allocation failure

    new->y = y;
    new->x = x;
    new->next = NULL;

    if (!*vecs)
        *vecs = new;
    else
    {
        t_vec *tmp = *vecs;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

/**
 * Determines if the specified direction is valid (i.e., points to a wall).
 *
 * @param m The map array.
 * @param dy The y-coordinate to check.
 * @param dx The x-coordinate to check.
 * @return 0 if the direction points to a wall ('1'), 1 otherwise.
 */
int is_valid_direction(char **m, int dy, int dx)
{
    return (m[dy] && m[dy][dx] && m[dy][dx] == '1') ? 0 : 1;
}

/**
 * Fills an array with the four possible movement directions (up, down, left, right).
 *
 * @param d The array to fill with direction vectors.
 */
void fill_directions(int d[4][2])
{
    d[0][0] = -1; d[0][1] = 0;  // Up
    d[1][0] = 0;  d[1][1] = 1;  // Right
    d[2][0] = 0;  d[2][1] = -1; // Left
    d[3][0] = 1;  d[3][1] = 0;  // Down
}

/**
 * Recursively checks if spaces outside the current coordinate are valid.
 *
 * @param vecs Pointer to the vector list for tracking checked coordinates.
 * @param m The map array.
 * @param y The y-coordinate of the current position.
 * @param x The x-coordinate of the current position.
 * @return 1 if the spaces are outside valid bounds or an invalid path, 0 otherwise.
 */
int is_spaces_outside(t_vec **vecs, char **m, int y, int x)
{
    if (!m[y] || !m[y][x])
        return 1;
    if (m[y][x] == '0')
        return 0;

    int directions[4][2];
    fill_directions(directions);
    add_vec(vecs, y, x);
    
    for (int i = 0; i < 4; i++)
    {
        int dy = y + directions[i][0];
        int dx = x + directions[i][1];
        if (is_valid_direction(m, dy, dx) && !has_vec(*vecs, dy, dx))
            if (is_spaces_outside(vecs, m, dy, dx))
                return 1;
    }
    return 0;
}
