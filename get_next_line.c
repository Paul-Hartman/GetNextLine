/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:17:46 by phartman          #+#    #+#             */
/*   Updated: 2024/05/07 17:05:48 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char *get_line(int fd)
{
	char *line;
	char *buf;
	ssize_t size_read;
	static t_list *stash;
	if(!stash)
		stash = ft_lstnew(NULL);
	buf = malloc(BUFFER_SIZE);
	if (!buf) return (NULL);
	size_read = read(fd, buf, BUFFER_SIZE);
	if (size_read > 0)
		stash->content = ft_strdup(buf);
	while(size_read > 0)
	{
		size_read = read(fd, buf, BUFFER_SIZE);
		ft_lstadd_back(&stash, ft_lstnew(ft_strdup(buf)));
	}
	return (line);
}


char *get_next_line(int fd)
{
	static int ct;
	int i;
	char ch;
	ssize_t size_read;
	
	ct = 0;
	i=0;
	while(size_read > 0 && i < ct)
	{
		size_read = read(fd, &ch, 1);
		if(ch == '\n')
			i++;
	}
	ct++;
	return (get_line(fd));
}



int main(int argc, char const *argv[])
{
	char *str;
	int fd;
	int i = 0;
	fd = open("testfile.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("failed to open");
		return (1);
	}
	while(i < 14)
	{
		str = get_next_line(fd);
		printf("%s", str);
		i++;
	}
	close(fd);
	return 0;
}
