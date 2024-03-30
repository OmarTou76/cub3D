#include "../../include/cub3D.h"

/*
		1111111111111111111111111
		1000000000110000000000001
		1011000001110000000000001
		1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
 */

int	get_map_height(t_node *node)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = node;
	while (tmp && ft_strlen(tmp->line))
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	copy_to_map(t_node **node, char ***map)
{
	int		map_height;
	t_node	*tmp;
	int		i;

	map_height = get_map_height(*node);
	(*map) = malloc((map_height + 1) * sizeof(char *));
	tmp = *node;
	i = 0;
	while (tmp && ft_strlen(tmp->line))
	{
		(*map)[i] = tmp->line;
		i++;
		tmp = tmp->next;
	}
	map[i] = NULL;
}

void	get_start_pos(t_vec *init, char *first_line)
{
	int	i;

	i = 0;
	while (first_line[i] && first_line[i] == ' ')
		i++;
	if (first_line[i] != '1')
		init->x = -1;
	else
		init->x = i;
	init->y = 0;
}

void	fill_dir(t_vec dir[4])
{
	dir[0].x = 1;
	dir[0].y = 0;
	dir[1].x = 0;
	dir[1].y = 1;
	dir[2].x = -1;
	dir[2].y = 0;
	dir[3].x = 0;
	dir[3].y = -1;
}

int	check_lines(char **m)
{
	int		x;
	int		y;
	t_vec	pos;

	y = 0;
	while (m[y])
	{
		x = 0;
		while (m[y][x] && m[y][x] == ' ')
			x++;
		pos.x = x;
		pos.y = y;
		if (m[y][x] != '1')
			return (0);
		while (m[y][x])
		{
			if ((!m[y][x + 1] || m[y][x + 1] == ' ') && m[y][x] == '0')
				return (0);
			else if (m[y][x] == ' ' && (m[y][x + 1] && m[y][x + 1] == '0'))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_columns(char **m, int map_height)
{
	int		x;
	int		y;
	t_vec	pos;

	x = 0;
	(void)map_height;
	while (m[0][x])
	{
		y = 0;
		while (m[y][x] == ' ')
			y++;
		pos.y = y;
		pos.x = x;
		if (m[y][x] != '1')
			return (0);
		while (m[y])
		{
			if ((!m[y + 1] || !m[y + 1][x] || m[y + 1][x] == ' ')
				&& m[y][x] == '0')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int	check_map_edges(char **m, int map_height)
{
	int	lines;
	int	cols;

	lines = check_lines(m);
	cols = check_columns(m, map_height);
	printf("LINES: %d - COLS: %d\n", lines, cols);
	return (1);
}

int	is_valid_map(t_node **node)
{
	char **map;
	// int i = 0;

	map = NULL;
	copy_to_map(node, &map);
	/* while (map[i])
	{
		printf("[%s]\n", map[i]);
		i++;
	} */
	check_map_edges(map, get_map_height(*node));
	exit(1);
	return (0);
}