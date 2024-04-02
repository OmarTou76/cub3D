#include "../../include/cub3D.h"

void	save_line(t_node **node, char *line)
{
	t_node	*nw;
	t_node	*tmp;

	nw = malloc(sizeof(t_node));
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

t_node	*save_data(char const *filename)
{
	int		fd;
	char	*line;
	t_node	*node;

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

void	free_nodes(t_node *node)
{
	t_node *tmp;

	while (node)
	{
		tmp = node->next;
		free(node->line);
		free(node);
		node = tmp;
	}
}