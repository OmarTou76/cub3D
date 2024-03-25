#include "../../include/cub3D.h"

int	is_valid_ext(char const* filename)
{
	char *ext;

	ext = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if (!ext || ft_strncmp(ext, ".cub", ft_strlen(ext)) != 0)
		return (0);
	return (1);
}