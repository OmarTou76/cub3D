/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:24:25 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/09 14:25:02 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BUFFER_SIZE 1

static size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while (i < srcsize && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

char	*ft_strdup_gnl(const char *src)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(src) + 1;
	dst = malloc(len);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy_gnl(dst, src, len);
	return (dst);
}

static char	*ft_strjoin_gnl(char *s1, char const *s2, size_t len)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = len;
	join = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy_gnl(join, s1, s1_len + 1);
	ft_strlcpy_gnl((join + s1_len), s2, s2_len + 1);
	free(s1);
	return (join);
}

char	*get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1];
	char *line;
	char *newline;
	int countread;
	int to_copy;

	line = ft_strdup_gnl(buf);
	while (!(ft_strchr(line, '\n')) && (countread = read(fd, buf,
				BUFFER_SIZE)) > 0)
	{
		buf[countread] = '\0';
		line = ft_strjoin_gnl(line, buf, countread);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);

	newline = ft_strchr(line, '\n');
	if (newline != NULL)
	{
		to_copy = newline - line + 1;
		ft_strlcpy_gnl(buf, newline + 1, BUFFER_SIZE + 1);
	}
	else
	{
		to_copy = ft_strlen(line);
		ft_strlcpy_gnl(buf, "", BUFFER_SIZE + 1);
	}
	line[to_copy] = '\0';
	return (line);
}