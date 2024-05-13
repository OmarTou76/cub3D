/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:38:27 by ymeziane          #+#    #+#             */
/*   Updated: 2024/05/12 20:37:40 by ymeziane         ###   ########.fr       */
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
	return (NULL);
}

static bool	textures_are_valid(t_game *game)
{
	if (!game->textures.east || !game->textures.west || !game->textures.south
		|| !game->textures.north)
	{
		if (game->textures.east)
			mlx_delete_image(game->mlx, game->textures.east);
		if (game->textures.west)
			mlx_delete_image(game->mlx, game->textures.west);
		if (game->textures.south)
			mlx_delete_image(game->mlx, game->textures.south);
		if (game->textures.north)
			mlx_delete_image(game->mlx, game->textures.north);
		printf("[ERROR]: Please provide correct textures\n");
		return (false);
	}
	return (true);
}

static bool	tex_animation_are_valid(t_game *game)
{
	if (!game->animation.crack || !game->animation.pistol[0]
		|| !game->animation.pistol[1] || !game->animation.pistol[2]
		|| !game->animation.pistol[3] || !game->animation.reticle)
	{
		if (game->animation.crack)
			mlx_delete_image(game->mlx, game->animation.crack);
		if (game->animation.pistol[0])
			mlx_delete_image(game->mlx, game->animation.pistol[0]);
		if (game->animation.pistol[1])
			mlx_delete_image(game->mlx, game->animation.pistol[1]);
		if (game->animation.pistol[2])
			mlx_delete_image(game->mlx, game->animation.pistol[2]);
		if (game->animation.pistol[3])
			mlx_delete_image(game->mlx, game->animation.pistol[3]);
		if (game->animation.reticle)
			mlx_delete_image(game->mlx, game->animation.reticle);
		printf("[ERROR]: Please provide correct animation textures\n");
		return (false);
	}
	return (true);
}

static bool	init_and_load_animation(t_game *game)
{
	game->animation.crack = get_img_from_texture(game->mlx,
			"./textures/animation/target.png");
	game->animation.pistol[0] = get_img_from_texture(game->mlx,
			"./textures/animation/pistol.png");
	game->animation.pistol[1] = get_img_from_texture(game->mlx,
			"./textures/animation/pistol2.png");
	game->animation.pistol[2] = get_img_from_texture(game->mlx,
			"./textures/animation/pistol3.png");
	game->animation.pistol[3] = get_img_from_texture(game->mlx,
			"./textures/animation/pistol4.png");
	game->animation.reticle = get_img_from_texture(game->mlx,
			"./textures/animation/reticle.png");
	return (tex_animation_are_valid(game));
}

bool	init_and_load_textures(t_game *game)
{
	if (!init_and_load_animation(game))
		return (false);
	game->textures.east = get_img_from_texture(game->mlx, game->paths->ea);
	game->textures.south = get_img_from_texture(game->mlx, game->paths->so);
	game->textures.west = get_img_from_texture(game->mlx, game->paths->we);
	game->textures.north = get_img_from_texture(game->mlx, game->paths->no);
	return (textures_are_valid(game));
}
