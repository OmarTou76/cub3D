#include "../../include/cub3D.h"

void	save_line(t_lines **node, char *line)
{
	t_lines	*nw;
	t_lines	*tmp;

	nw = malloc(sizeof(t_lines));
	nw->line = ft_strdup(line);
	nw->next = NULL;
	if (nw->line[ft_strlen(nw->line) - 1] == '\n')
		nw->line[ft_strlen(nw->line) - 1] = 0;
	if (!*node)
		(*node) = nw;
	else
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = nw;
	}
}

t_lines	*save_data(char const *filename)
{
	int		fd;
	char	*line;
	t_lines	*node;

	node = NULL;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		save_line(&node, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (node);
}

void	free_nodes(t_lines *node)
{
	t_lines *tmp;

	while (node)
	{
		tmp = node->next;
		free(node->line);
		free(node);
		node = tmp;
	}
}