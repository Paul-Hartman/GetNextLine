/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:17:46 by phartman          #+#    #+#             */
/*   Updated: 2024/05/07 19:20:10 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char *get_next_line(int fd)
{
	char *line;
	char *buf;
	ssize_t size_read;
	static t_list *stash;
	char *newline;
	t_list *current;
	if(!stash)
		stash = ft_lstnew(NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf) return (NULL);
	size_read = read(fd, buf, BUFFER_SIZE);
	if (size_read > 0)
		stash->content = ft_strndup(buf, BUFFER_SIZE +1);
	newline = ft_strchr(buf, '\n');
	while(size_read > 0 && !newline)
	{
		size_read = read(fd, buf, BUFFER_SIZE);
		
		// if(newline)
		// {
		// 	ft_lstadd_back(&stash, ft_lstnew(ft_strndup(buf, (newline - buf)+1)));
		// 	ft_lstadd_back(&stash, ft_lstnew(ft_strndup(newline + 1, ft_strlen(newline)-1)));
		// 	break;
		//current->content[ft_strlen(current->content) - 1] != '\n' &&
		// }
		ft_lstadd_back(&stash, ft_lstnew(ft_strndup(buf, BUFFER_SIZE +1)));
	}
	if(newline)
		{
			ft_lstlast(stash)->content = ft_strndup(buf, (newline - buf)+1);
			ft_lstadd_back(&stash, ft_lstnew(ft_strndup(newline + 1, ft_strlen(newline)-1)));
		}
	line = malloc(ft_lstsize(stash) * BUFFER_SIZE);
	ft_strlcpy(line, stash->content, BUFFER_SIZE);
	stash->content = newline + 1;
	current = stash->next;
	while(current &&  current->content[ft_strlen(current->content) - 1] != '\n')
	{
		ft_strlcat(line, current->content, BUFFER_SIZE + 1);
		current = current->next;
	}
	return (line);
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
	while(i < 5)
	{
		str = get_next_line(fd);
		printf("%s", str);
		i++;
	}
	close(fd);
	return 0;
}
