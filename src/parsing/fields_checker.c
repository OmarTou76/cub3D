#include "../../include/cub3D.h"

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

int	trim_compare(char *base, char *to_compare, size_t size)
{
	while (*base && *base == ' ')
		base++;
	return (ft_strncmp(base, to_compare, size));
}

int	is_valid_number(char *nb)
{
	int	i;

	i = 0;
	while (nb[i] && nb[i] == ' ')
		i++;
	while (nb[i] && ft_isdigit(nb[i]))
		i++;
	if (nb[i] || (ft_atoi(nb) > 255 || ft_atoi(nb) < 0))
		return (0);
	return (1);
}

int	is_valid_RGB_data(char *line)
{
	char	**data;
	int		i;
	int		valid_data;

	i = 0;
	valid_data = 1;
	while (*line && !ft_isdigit(*line))
		line++;
	if (!*line)
		return (0);
	data = ft_split(line, ',');
	while (data[i])
	{
		if (!is_valid_number(data[i]))
			valid_data = 0;
		free(data[i]);
		i++;
	}
	if (i != 3)
		valid_data = 0;
	free(data);
	return (valid_data);
}

int	check_fields(char *line, t_fields *fields)
{
	if (trim_compare(line, "NO ", 3) == 0)
		fields->NO++;
	else if (trim_compare(line, "EA ", 3) == 0)
		fields->EA++;
	else if (trim_compare(line, "SO ", 3) == 0)
		fields->SO++;
	else if (trim_compare(line, "WE ", 3) == 0)
		fields->WE++;
	else if (trim_compare(line, "C ", 2) == 0 && is_valid_RGB_data(line))
		fields->C++;
	else if (trim_compare(line, "F ", 2) == 0 && is_valid_RGB_data(line))
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
