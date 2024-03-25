#include "../../include/cub3D.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while ((unsigned char)s1[i] == (unsigned char)s2[i])
	{
		if ((unsigned char)s1[i] == 0 || i == n - 1)
			return (0);
		i++;
	}
	if ((unsigned char)s1[i] < (unsigned char)s2[i])
		return (-1);
	return (1);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		continue ;
	return (i);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lillen;

	lillen = ft_strlen(little);
	i = -1;
	if (!little || !*little)
		return ((char *)big);
	while (big[++i] && i < len)
	{
		j = 0;
		while (little[j] && big[j + i] && j + i < len)
		{
			if (little[j] != big[j + i])
				break ;
			j++;
		}
		if (lillen == j)
			return ((char *)big + i);
	}
	return (0);
}
