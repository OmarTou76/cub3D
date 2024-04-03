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

int get_map_height(t_lines *node)
{
	int i;
	t_lines *tmp;

	i = 0;
	tmp = node;
	while (tmp && ft_strlen(tmp->line))
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char **node_to_map(t_lines **node)
{
	t_lines *tmp;
	int i;
	int map_height;
	char **map;

	map_height = get_map_height(*node);
	map = malloc((map_height + 1) * sizeof(char *));
	tmp = *node;
	i = 0;
	
	while (tmp && ft_strlen(tmp->line))
	{
		map[i] = tmp->line;
		i++;
		tmp = tmp->next;
	}
	map[i] = NULL;
	return (map);
}

void get_start_pos(t_vec *init, char *first_line)
{
	int i;

	i = 0;
	while (first_line[i] && first_line[i] == ' ')
		i++;
	if (first_line[i] != '1')
		init->x = -1;
	else
		init->x = i;
	init->y = 0;
}

int check_lines(char **m)
{
	int x;
	int y;

	y = 0;
	while (m[y])
	{
		x = 0;
		while (m[y][x] && m[y][x] == ' ')
			x++;
		if (m[y][x] != '1')
			return (0);
		while (m[y][x])
		{
			if ((!m[y][x + 1] || m[y][x + 1] == ' ') && m[y][x] == '0')
				return (0);
			else if ((m[y][x] == ' ' && (m[y][x + 1] && m[y][x + 1] == '0')))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int check_columns(char **m)
{
	int x;
	int y;

	x = 0;
	while (m[0][x])
	{
		y = 0;
		while (m[y][x] == ' ')
			y++;
		if (m[y][x] != '1')
			return (0);
		while (m[y])
		{
			if ((!m[y + 1] || !m[y + 1][x] || m[y + 1][x] == ' ') && m[y][x] == '0')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int check_map_borders(char **m)
{
	if (!check_columns(m) || !check_lines(m))
	{
		printf("Error\nMap borders\n");
		return (0);
	}
	return (1);
}

int check_start_pos(char **map)
{
	int y;
	int x;
	int count;
	char c;

	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				count++;
			if (count > 1)
			{
				printf("Error\nMultiple start position\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int is_valid_map(t_lines **node)
{
	char **map;

	map = node_to_map(node);
	if (!check_map_borders(map) || !check_start_pos(map))
		return (free(map), 0);
	free(map);
	return (1);
}