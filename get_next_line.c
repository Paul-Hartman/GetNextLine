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


void list_clear(t_list **head)
{
	t_list *current = *head;
	t_list *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}

	*head = NULL;
}

// char *get_next_line(int fd)
// {
// 	char *line;
// 	char *buf;
// 	ssize_t size_read;
// 	static t_list *stash;
// 	char *newline;
// 	t_list *current;
// 	buf = malloc(BUFFER_SIZE + 1);
	
// 	size_read = 1;
// 	if (!buf || !newline) return (NULL);
// 	*buf = "\0";
// 	if (size_read > 0 && !stash)
// 	{
// 		size_read = read(fd, buf, BUFFER_SIZE);
// 		newline = ft_strchr(buf, '\n');
// 		if(!stash)
// 			stash =  ft_lstnew(ft_strndup(buf, BUFFER_SIZE +1));
// 		while(size_read > 0 && !newline)
// 		{
// 			size_read = read(fd, buf, BUFFER_SIZE);
// 			newline = ft_strchr(buf, '\n');
// 			if(newline) break;
// 			ft_lstadd_back(&stash, ft_lstnew(ft_strndup(buf, BUFFER_SIZE +1)));
// 		}


// 	}
// 	else
// 	{
// 		newline = ft_strchr(stash->content, '\n');
		
// 	}
	
	
	
// 	if(newline)
// 	{
		
// 		if (size_read !=0)
// 		{
// 			ft_lstadd_back(&stash, ft_lstnew(ft_strndup(buf, (newline - buf)+1)));
// 			ft_lstadd_back(&stash, ft_lstnew(ft_strndup(newline + 1, ft_strlen(newline)-1)));
			
// 		}
// 		else
// 		{
			
// 			stash->content = ft_strndup(stash->content, (newline - stash->content)+1);
// 			ft_lstadd_back(&stash, ft_lstnew(ft_strndup(newline + 1, ft_strlen(newline)-1)));
// 		}
		
// 	}
// 	line = malloc(ft_lstsize(stash) * BUFFER_SIZE + 1);
// 	if (!line) return (NULL);
	
	
// 	ft_strlcat(line, stash->content, ft_lstsize(stash) * BUFFER_SIZE);
// 	current = stash->next;
// 	while(current)
// 	{
// 		ft_strlcat(line, current->content, ft_lstsize(stash) * BUFFER_SIZE);
// 		if (current->content[ft_strlen(current->content) - 1] == '\n') break;
// 		current = current->next;
// 	}
// 	if(stash->next)
// 	{
// 		stash->content = ft_strndup(ft_lstlast(stash)->content, ft_strlen(ft_lstlast(stash)->content) + 1);
		
// 	}
// 	else
// 		stash == NULL;
// 	list_clear(&(stash->next));
// 	free(buf);
// 	return (line);
// }




char *get_next_line(int fd)
{
	char *line;
	char *buf;
	ssize_t size_read;
	static t_list *stash;
	char *newline;
	t_list *current;
	buf = malloc(BUFFER_SIZE + 1);
	newline= NULL;
	
	size_read = 1;
	if (!buf) return (NULL);
	if (!stash)
	{	
		while (!newline && size_read > 0)
		{
			size_read = read(fd, buf, BUFFER_SIZE);
			ft_lstadd_back(&stash, ft_lstnew(ft_strdup(buf)));
			current = ft_lstlast(stash);
			newline = ft_strchr(current->content, '\n');
		}
	}
	else
	{
		newline = ft_strchr(stash->content, '\n');
		current = ft_lstlast(stash);
		while (!newline && size_read > 0)
		{
			size_read = read(fd, buf, BUFFER_SIZE);
			ft_lstadd_back(&stash, ft_lstnew(ft_strdup(buf)));
			current = ft_lstlast(stash);
			newline = ft_strchr(current->content, '\n');
		}
	}
	if(newline)
	{
		current->content = ft_substr(current->content, 0, (newline - current->content)+1);
		if(newline[1])
			ft_lstadd_back(&stash, ft_lstnew(ft_substr(newline, 1, ft_strlen(newline)-1)));
	}
	line = calloc(ft_lstsize(stash), BUFFER_SIZE + 1);
	if (!line) return (NULL);
	current = stash;
	while(current)
	{
		ft_strlcat(line, current->content, ft_lstsize(stash) * BUFFER_SIZE);
		if (current->content[ft_strlen(current->content) - 1] == '\n') break;
		current = current->next;
		
	}
	if(stash->next)
	{
		current = current->next;
		stash->content = ft_strdup(current->content);
	}
	else
		stash == NULL;
	list_clear(&(stash->next));
	free(buf);
	buf = NULL;
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
		free(str);
		str = NULL;
		i++;
	}
	close(fd);
	return 0;
}
