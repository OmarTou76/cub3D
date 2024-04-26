/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:38:27 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/26 15:40:11 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static mlx_image_t	*get_img_from_texture(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	img = mlx_texture_to_image(mlx, texture);
	return (img);
}

void	init_and_load_textures(t_game *game)
{
	game->textures.east = get_img_from_texture(game->mlx, game->paths->ea);
	game->textures.south = get_img_from_texture(game->mlx, game->paths->so);
	game->textures.west = get_img_from_texture(game->mlx, game->paths->we);
	game->textures.north = get_img_from_texture(game->mlx, game->paths->no);
}