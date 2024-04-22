#include "cub3D.h"

int	is_round(double num)
{
	double	rounded;

	rounded = round(num);
	if (fabs(rounded - num) < 1e-6)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void	get_wall_img(t_wall *wall, t_game *game, double wall_y, double wall_x)
{
	int		player_y;
	int		player_x;
	double	y;
	double	x;

	player_y = game->player->img_player->instances[0].y / MAP_TILE_SIZE;
	player_x = game->player->img_player->instances[0].x / MAP_TILE_SIZE;
	if ((int)round(wall_y) / TILE_SIZE == 0)
		wall->img = game->textures.north;
	else if ((int)round(wall_y) / TILE_SIZE == (int)game->s_map.height - 1)
		wall->img = game->textures.south;
	else if ((int)round(wall_x) / TILE_SIZE == 0)
		wall->img = game->textures.west;
	else if ((int)round(wall_x) / TILE_SIZE == (int)game->s_map.width - 1)
		wall->img = game->textures.east;
	else
	{
		// Murs a l'interieur de la map ()
		// Trouver une solution pour afficher les bonnes textures
		y = wall_y / (double)TILE_SIZE;
		x = wall_x / (double)TILE_SIZE;
		printf("%d %d -> %f %f\n", player_y, player_x, y, x);
		if ((double)player_y < y && is_round(x))
		{
			wall->img = game->textures.east;
		}
		/* else if ((double)player_x < x && is_round(y))
		{
			wall->img = game->textures.west;
		} */
		else
			wall->img = game->textures.south;
	}
}

void	compute_distance_and_select_wall(t_game *game, t_wall *wall)
{
	t_direction_line	line;
	double				theta;
	double				y;
	double				x;
	double				step_y;
	double				step_x;

	line.start_x = game->player->img_player->instances[0].x * TILE_FACTOR;
	line.start_y = game->player->img_player->instances[0].y * TILE_FACTOR;
	y = line.start_y;
	x = line.start_x;
	theta = ((-wall->column_angle * M_PI) / 180.0);
	step_y = sin(theta) * .1;
	step_x = cos(theta) * .1;
	while (true)
	{
		if (game->s_map.map[(int)round(y) / TILE_SIZE][(int)round(x)
			/ TILE_SIZE] == '1')
		{
			get_wall_img(wall, game, y, x);
			wall->distance = (sqrt(pow(x - line.start_x, 2) + pow(y
							- line.start_y, 2)));
			return ;
		}
		x += step_x;
		y += step_y;
	}
}

void	get_wall(t_game *game, t_wall *wall, double left_angle, int index)
{
	int	column_count;

	column_count = game->img_view_3d->width;
	wall->column_angle = left_angle + (index * FOV / column_count);
	compute_distance_and_select_wall(game, wall);
	wall->height = ((TILE_SIZE * game->s_map.height) / wall->distance)
		* (TILE_SIZE / 2);
}

uint32_t	get_pixel_from_texture(t_game *game, t_wall wall, int y, int x)
{
	float	texture_y;
	int		texture_index;

	texture_y = ((float)(y - (game->img_view_3d->height - wall.height) / 2)
			/ wall.height) * wall.img->height;
	texture_index = ((int)texture_y * wall.img->width + x) % (wall.img->width
			* wall.img->height);
	return (convert_rgba_to_argb(((uint32_t *)wall.img->pixels)[texture_index]));
}

void	draw_column(t_game *game, t_wall wall, int index)
{
	int	texture_x;
	int	y;
	int	y_start;

	texture_x = (index % wall.img->width);
	y_start = (game->img_view_3d->height - wall.height) / 2;
	y = 0;
	while (y < (int)game->img_view_3d->height)
	{
		if (y >= y_start && y <= y_start + wall.height)
		{
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, get_pixel_from_texture(game, wall, y, texture_x));
		}
		else if (y < y_start)
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, ft_pixel(game->colors->ceiling[0], game->colors->ceiling[1],
					game->colors->ceiling[2], 0xFF));
		else if (y > y_start + wall.height)
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, ft_pixel(game->colors->floor[0], game->colors->floor[1],
					game->colors->floor[2], 0xFF));
		y++;
	}
}

void	raycast(t_game *game)
{
	int col_nb;
	int index;
	double left_angle;
	t_wall wall;

	col_nb = game->img_view_3d->width;
	index = 1;
	left_angle = game->player->angle - (FOV / 2);
	while (index < col_nb)
	{
		get_wall(game, &wall, left_angle, index);
		draw_line_on_map(game, wall.column_angle);
		draw_column(game, wall, index);
		index++;
	}
}