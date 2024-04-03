#include "../../include/cub3D.h"

int	check_input(char const *progname, char const *filename, int argc)
{
	char	*ext;

	if (argc != 2)
		return(printf("Error\n[USAGE]: %s <FILENAME>.cub .\n", progname), 0);
	ext = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if(open(filename, O_RDONLY) == -1)
		return(printf("Error\n"), perror(filename), 0);
	else
		close(open(filename, O_RDONLY));
	if (!ext || ft_strncmp(ext, ".cub", ft_strlen(ext)) != 0)
		return(printf("Error\n[USAGE]: %s <FILENAME>.cub .\n", progname), 0);
	return (1);
}

int	is_map_start(char *line)
{
	int	i;	

	i = 0;
	if (!ft_strlen(line))
		return (0);
	while (line[i] && (line[i] == '1' || line[i] == ' '))
		i++;
	if (line[i])
		return (0);
	return (1);
}

int	is_valid_data(t_lines *node)
{
	t_lines *tmp;
	t_fields fields;

	tmp = node;
	if (!tmp)
	{
		printf("Error\nMap empty\n");
		return (0);
	}
	init_fields(&fields);
	while (tmp)
	{
		if (ft_strlen(tmp->line) && !fields.is_ok && !is_map_start(tmp->line)
			&& !check_fields(tmp->line, &fields))
		{
			printf("Error\nInvalid fields input\n");
			return (0);
		}
		if (ft_strlen(tmp->line) && is_map_start(tmp->line))
		{
			if (fields.is_ok && is_valid_map(&tmp))
				return (1);
			else
			{
				printf("Error\nMissing params\n");
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}