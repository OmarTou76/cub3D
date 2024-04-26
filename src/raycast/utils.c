#include "cub3D.h"

uint32_t	convert_rgba_to_argb(uint32_t rgba)
{
	uint8_t red = (rgba >> 24) & 0xFF;   // Extract red
	uint8_t green = (rgba >> 16) & 0xFF; // Extract green
	uint8_t blue = (rgba >> 8) & 0xFF;   // Extract blue
	uint8_t alpha = rgba & 0xFF;         // Extract alpha
	return ((alpha << 24) | (blue << 16) | (green << 8) | red);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

mlx_image_t	*get_img_from_texture(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (texture)
		return (mlx_texture_to_image(mlx, texture));
	printf("ERROR: Incorrect path or extension (%s)\n", path);
	return (NULL);
}

bool	textures_are_valid(t_game *game)
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