/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:38:27 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/26 19:29:56 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static mlx_image_t	*get_img_from_texture(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	if (texture)
	{
		img = mlx_texture_to_image(mlx, texture);
		mlx_delete_texture(texture);
		return (img);
	}
	printf("[ERROR]: Impossible to load texture at %s\n", path);
	return (NULL);
}

static bool	textures_are_valid(t_game *game)
{
	if (game->textures.east == NULL || game->textures.west == NULL
		|| game->textures.south == NULL || game->textures.north == NULL)
	{
		if (game->textures.east != NULL)
			mlx_delete_image(game->mlx, game->textures.east);
		if (game->textures.west != NULL)
			mlx_delete_image(game->mlx, game->textures.west);
		if (game->textures.south != NULL)
			mlx_delete_image(game->mlx, game->textures.north);
		if (game->textures.north != NULL)
			mlx_delete_image(game->mlx, game->textures.north);
		return (false);
	}
	return (true);
}

bool	init_and_load_textures(t_game *game)
{
	game->textures.east = get_img_from_texture(game->mlx, game->paths->ea);
	game->textures.south = get_img_from_texture(game->mlx, game->paths->so);
	game->textures.west = get_img_from_texture(game->mlx, game->paths->we);
	game->textures.north = get_img_from_texture(game->mlx, game->paths->no);
	return (textures_are_valid(game));
}