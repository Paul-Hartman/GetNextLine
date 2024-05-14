/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:29:25 by phartman          #+#    #+#             */
/*   Updated: 2024/05/14 18:09:24 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	uc = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == uc)
			return ((char *)&s[i]);
		i++;
	}
	if (uc == 0)
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	i = 0;
	dup = malloc(ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len < size)
	{
		i = dst_len;
		j = 0;
		while (i < size -1 && src[j])
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
	}
	if (size <= dst_len)
		return (src_len + size);
	return (dst_len + src_len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*memdest;
	const unsigned char	*memsrc;
	size_t				i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	memdest = dest;
	memsrc = src;
	while (i < n)
	{
		memdest[i] = memsrc[i];
		i++;
	}
	return (dest);
}

