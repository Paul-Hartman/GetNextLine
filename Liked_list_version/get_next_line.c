#include "get_next_lineLL.h"


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

char *get_next_line(int fd)
{
	char *line;
	char *buf;
	ssize_t size_read;
	static t_list *stash;
	char *newline;
	t_list *current;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf) return (NULL);
	newline= NULL;
	
	size_read = 1;
	
	if (!stash)
	{	
		while (!newline && size_read > 0)
		{
			size_read = read(fd, buf, BUFFER_SIZE);
			buf[size_read] = '\0';
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
			buf[size_read] = '\0';
			ft_lstadd_back(&stash, ft_lstnew(ft_strdup(buf)));
			current = ft_lstlast(stash);
			newline = ft_strchr(current->content, '\n');
		}
	}
	if(newline)
	{
		char *temp = current->content;
		current->content = ft_substr(current->content, 0, (newline - current->content)+1);
		if(newline[1] && ft_strlen(newline) > 0)
			ft_lstadd_back(&stash, ft_lstnew(ft_substr(newline, 1, ft_strlen(newline)-1)));
		if(temp != current->content)
		{
			free(temp);
			temp = NULL;
		}
			
	}

	line = malloc(ft_lstsize(stash) * BUFFER_SIZE + 1);
	line[0] = '\0';
	if (!line) return (NULL);
	current = stash;
	while(current)
	{
		ft_strlcat(line, current->content, (ft_lstsize(stash) * BUFFER_SIZE)+1);
		if (ft_strlen(current->content) > 0 && current->content[ft_strlen(current->content) - 1] == '\n') break;
		current = current->next;
	}
	if(size_read > 0 && current && current->content)
	{
		current = current->next;
		
		char *temp = stash->content;
		if(current)
			stash->content = ft_strdup(current->content);
		free(temp);
		temp = NULL;
		list_clear(&(stash->next));
	}
	else
	{
		list_clear(&(stash));
		stash = NULL;
	}
		
	free(buf);
	buf = NULL;
	return (line);
}
