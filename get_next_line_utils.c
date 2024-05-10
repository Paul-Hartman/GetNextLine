/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:18:21 by phartman          #+#    #+#             */
/*   Updated: 2024/05/07 18:51:20 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (*lst == NULL)
		*lst = new;
	else
	{
		end = ft_lstlast(*lst);
		if (end)
			end->next = new;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		if(lst->next == NULL)
			break;
		lst = lst->next;
	}
	return (i);
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


