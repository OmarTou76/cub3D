#include "../../include/cub3D.h"

void	get_textures_paths(t_game *game, t_node **node)
{
	t_node	*tmp;

	(void)game;
	tmp = *node;
	while (tmp)
	{
		tmp = tmp->next;
	}
}

void	store_data(t_game *game, t_node *node)
{
	(void)game;
	get_textures_paths(game, &node);
}