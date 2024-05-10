#include "cub3D.h"

static void	init_line_length(t_game *game)
{
	if (game->map.img_map->height > game->map.img_map->width)
		game->map.rays.length = game->map.img_map->height;
	else
		game->map.rays.length = game->map.img_map->width;
}

void	init_and_draw_line(mlx_t *mlx, t_game *game)
{
	init_line_length(game);
	game->map.rays.img_line = mlx_new_image(mlx, game->map.rays.length * 2,
			game->map.rays.length * 2);
	mlx_image_to_window(mlx, game->map.rays.img_line, 0, 0);
	mlx_set_instance_depth(game->map.rays.img_line->instances, 3);
	game->map.rays.img_line->enabled = false;
}

void	init_and_draw_map(t_game *game)
{
	unsigned int y;
	unsigned int x;

	game->map.img_map = mlx_new_image(game->mlx, (game->map.width
				* game->map.tile_size), game->map.height * game->map.tile_size);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width && ft_strlen(game->map.map[y]) > x)
		{
			if (game->map.map[y][x] == '1')
				fill_by_pixel(game->map, (y * game->map.tile_size), (x
						* game->map.tile_size), ft_pixel(0, 0, 0, 0xFF));
			else if (game->map.map[y][x] == 'D')
				fill_by_pixel(game->map, (y * game->map.tile_size), (x
						* game->map.tile_size), ft_pixel(0, 200, 200, 0xFF));
			else
				fill_by_pixel(game->map, (y * game->map.tile_size), (x
						* game->map.tile_size), ft_pixel(150, 150, 150, 0x90));
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, game->map.img_map, game->map.padding_x,
		game->map.padding_y);
	mlx_set_instance_depth(game->map.img_map->instances, 2);
	game->map.img_map->enabled = false;
}