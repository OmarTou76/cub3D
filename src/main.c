#include "../include/cub3D.h"

int	main(int argc, char const *argv[])
{
	t_node	*node;

	// t_game	game;
	if (argc != 2 || !is_valid_ext(argv[1]))
	{
		printf("Error\n[USAGE]: %s <FILENAME>.cub .\n", argv[0]);
		return (1);
	}
	node = save_data(argv[1]);
	if (!is_valid_map(node))
		return (1);
	// store_data(&game, node);
	/* while (node)
	{
		printf("[%s]\n", node->line);
		node = node->next;
	} */
	return (0);
}
