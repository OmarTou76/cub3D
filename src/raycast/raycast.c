#include "cub3D.h"

int	r(double nb)
{
	return (int)round(nb);
}

void	get_wall_img(t_wall *wall, t_game *game)
{
	int	round_y;
	int	round_x;
	int	player_x;
	int	player_y;

	// Trouver la bonne texture a afficher
	player_x = game->player->img_player->instances[0].x / MAP_TILE_SIZE;
	player_y = game->player->img_player->instances[0].y / MAP_TILE_SIZE;
	round_y = r(wall->collision_y);
	round_x = r(wall->collision_x);
	printf("P: %d %d -> W: [%d][%d] -> [%c]\n", player_y, player_x, round_y,
		round_x, game->s_map.map[round_y][round_x]);
	// -----------
	wall->img = game->textures.south;
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
		if (game->s_map.map[r(y) / TILE_SIZE][r(x) / TILE_SIZE] == '1')
		{
			wall->collision_y = y / TILE_SIZE;
			wall->collision_x = x / TILE_SIZE;
			get_wall_img(wall, game);
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
	wall->height = (game->img_view_3d->height / wall->distance) * (TILE_SIZE);
}

uint32_t	get_pixel_from_texture(t_wall wall, int y)
{
	double	texture_x;
	double	texture_y;
	int		texture_index;
	double	fract_x;
	double	fract_y;

	fract_x = fmod(wall.collision_x, 1.0f);
	fract_y = fmod(wall.collision_y, 1.0f);
	if (fract_x < 0.98 || fract_y > 0.98)
		texture_x = fract_x;
	else
		texture_x = fract_y;
	texture_y = (double)y / wall.height;
	texture_index = ((int)(texture_y * wall.img->height) * wall.img->width)
		+ (int)(texture_x * wall.img->width);
	texture_index %= (wall.img->height * wall.img->width);
	return (convert_rgba_to_argb(((uint32_t *)wall.img->pixels)[texture_index]));
}

void	draw_column(t_game *game, t_wall wall, int index)
{
	int			y_start;
	int			y;
	uint32_t	color;

	y_start = (game->img_view_3d->height - wall.height) / 2;
	y = 0;
	while (y < (int)game->img_view_3d->height)
	{
		if (y < y_start)
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, ft_pixel(game->colors->ceiling[0], game->colors->ceiling[1],
					game->colors->ceiling[2], 0xFF));
		else if (y > y_start + wall.height)
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, ft_pixel(game->colors->floor[0], game->colors->floor[1],
					game->colors->floor[2], 0xFF));
		else
		{
			color = get_pixel_from_texture(wall, y - y_start);
			mlx_put_pixel(game->img_view_3d, game->img_view_3d->width - index,
				y, color);
		}
		y++;
	}
}

void	raycast(t_game *game)
{
	int		col_nb;
	int		index;
	double	left_angle;
	t_wall	wall;

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
