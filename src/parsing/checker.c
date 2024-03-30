#include "../../include/cub3D.h"

int	is_valid_ext(char const *filename)
{
	char	*ext;

	ext = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if (!ext || ft_strncmp(ext, ".cub", ft_strlen(ext)) != 0)
		return (0);
	return (1);
}

int	is_map_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == '1' || line[i] == ' '))
		i++;
	if (line[i])
		return (0);
	return (1);
}
// CHECKER LE FAIT DE METTRE UN FIELD QUI NE COMMENCE PAS PAR CE DEMANDE
void	init_fields(t_fields *f)
{
	f->C = 0;
	f->F = 0;
	f->NO = 0;
	f->WE = 0;
	f->EA = 0;
	f->SO = 0;
	f->is_ok = 0;
}

int	check_fields(char *line, t_fields *fields)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i] || is_map_start(line))
		return (1);
	else if (ft_strncmp(line + i, "NO ", 3) == 0)
		fields->NO++;
	else if (ft_strncmp(line + i, "EA ", 3) == 0)
		fields->EA++;
	else if (ft_strncmp(line + i, "SO ", 3) == 0)
		fields->SO++;
	else if (ft_strncmp(line + i, "WE ", 3) == 0)
		fields->WE++;
	else if (ft_strncmp(line + i, "C ", 2) == 0)
		fields->C++;
	else if (ft_strncmp(line + i, "F ", 2) == 0)
		fields->F++;
	else
		return (0);
	if (fields->NO == 1 && fields->EA == 1 && fields->SO == 1 && fields->WE == 1
		&& fields->C == 1 && fields->F == 1)
		fields->is_ok = 1;
	else
		fields->is_ok = 0;
	return (1);
}

int	is_valid_data(t_node *node)
{
	t_node *tmp;
	t_fields fields;

	tmp = node;
	init_fields(&fields);
	while (tmp)
	{
		if (!check_fields(tmp->line, &fields))
		{
			printf("Error\nInvalid fields input\n");
			exit(1);
		}
		if (ft_strlen(tmp->line) && is_map_start(tmp->line))
		{
			if (!fields.is_ok)
			{
				printf("Error\nMissing fields params\n");
				exit(1);
			}
			else if (!is_valid_map(&tmp))
			{
				printf("Error\nWrong map\n");
				exit(1);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}