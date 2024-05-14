/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:14:45 by phartman          #+#    #+#             */
/*   Updated: 2024/05/14 18:15:26 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*mem;

	mem = s;
	while (n--)
		*mem++ = 0;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	true_len;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	true_len = str_len - start;
	if (true_len > len)
		true_len = len;
	sub = malloc(true_len + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, true_len);
	sub[true_len] = '\0';
	return (sub);
}

char	*add_to_string(char *str, char *buf)
{
	char	*newstr;
	int		size;

	if (!str || !buf)
		return (NULL);
	size = ft_strlen(str) + ft_strlen(buf) + 1;
	newstr = malloc(size);
	ft_bzero(newstr, size);
	ft_strlcat(newstr, str, size);
	ft_strlcat(newstr, buf, size);
	free(str);
	return (newstr);
}

char	*read_until_newline(char **newline, char **stash, int fd)
{
	char	*buf;
	ssize_t	readsize;

	if (*stash == NULL)
	{
		*stash = malloc(BUFFER_SIZE + 1);
		if (!*stash)
			return (NULL);
		*stash[0] = '\0';
	}
	readsize = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (*newline == NULL && readsize > 0)
	{
		readsize = read(fd, buf, BUFFER_SIZE);
		buf[readsize] = '\0';
		if (readsize == 0)
			break ;
		*stash = add_to_string(*stash, buf);
		*newline = ft_strchr(*stash, '\n');
	}
	free(buf);
	return (*newline);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[8192];
	char		*newline;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd > 8192)
		return (free(stash[fd]), stash[fd] = NULL);
	newline = NULL;
	temp = NULL;
	if (stash[fd])
		newline = ft_strchr(stash[fd], '\n');
	if (!read_until_newline(&newline, &stash[fd], fd))
		line = ft_strdup(stash[fd]);
	else
	{
		line = ft_substr(stash[fd], 0, (newline - stash[fd]) + 1);
		if (newline[1])
			temp = ft_substr(newline, 1, ft_strlen(newline) - 1);
	}
	free(stash[fd]);
	stash[fd] = temp;
	if (*line == '\0' || !line)
		return (free(line), NULL);
	return (line);
}
