#include "../include/cub3D.h"

void	print_data(t_game *game)
{
	printf("\nCOLORS: \n\n");
	printf("\tFLOOR: %d - %d - %d\n", game->colors->floor[0],
		game->colors->floor[1], game->colors->floor[2]);
	printf("\tCEILING: %d - %d - %d\n", game->colors->ceiling[0],
		game->colors->ceiling[1], game->colors->ceiling[2]);
	printf("\nTEXTURES: \n\n");
	printf("\tNO: %s\n", game->paths->NO);
	printf("\tEA: %s\n", game->paths->EA);
	printf("\tSO: %s\n", game->paths->SO);
	printf("\tWE: %s\n", game->paths->WE);
	printf("\n");
	printf("\nMAP:\n\n");
	int i = 0;
	while (game->map[i])
	{
		printf("\t%s\n", game->map[i]);
		i++;
	}
	printf("\n");
}

void	print_nodes(t_node *tmp)
{
	t_node	*node;

	node = tmp;
	while (node)
	{
		printf("[%s]\n", node->line);
		node = node->next;
	}
}

int	main(int argc, char const *argv[])
{
	t_node	*node;
	t_game	*game;

	if (argc != 2 || !is_valid_ext(argv[1]))
	{
		printf("Error\n[USAGE]: %s <FILENAME>.cub .\n", argv[0]);
		return (1);
	}
	node = save_data(argv[1]);
	if (!is_valid_data(node))
		return (free_nodes(node), 1);
	//print_nodes(node);
	store_data(&game, node);
	print_data(game);
	free_nodes(node);
}
