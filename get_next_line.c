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


char *add_to_string(char *str, char *buf)
{
	char *newstr;
	int size;

	if(!str || !buf)
		return (NULL);
	size = ft_strlen(str) + ft_strlen(buf) + 1;
	newstr = malloc(size);
	ft_bzero(newstr, size);
	ft_strlcat(newstr, str, size);
	ft_strlcat(newstr, buf, size);
	free(str);
	return(newstr);
}

char *read_until_newline(char **newline, char **stash, int fd)
{
	char *buf;
	ssize_t readsize;
	if(*stash == NULL)
	{
		*stash = malloc(BUFFER_SIZE +1);
		*stash[0] = '\0';
	}
	if(*stash == NULL) return (NULL);	
	readsize = 1;
	buf = malloc(BUFFER_SIZE + 1);
	ft_bzero(buf, BUFFER_SIZE + 1);
	if(!buf) return (NULL);
	while(*newline == NULL && readsize > 0)
	{
		readsize = read(fd, buf, BUFFER_SIZE);
		buf[readsize] = '\0';
		if (readsize == 0)break;
		if(readsize == -1)
		{
			
		} 
		*stash = add_to_string(*stash, buf);
		*newline = ft_strchr(*stash, '\n');
	}
	free(buf);
	buf = NULL;
	return(*stash);
}

char *get_next_line(int fd)
{
	char *line;
	static char *stash;
	char *newline;
	char *temp;

	if(fd < 0 || BUFFER_SIZE <=0 || read(fd, 0, 0) < 0)
		return (NULL);
	newline = NULL;
	if(stash)
		newline = ft_strchr(stash, '\n');
	if(!newline)
	{
		stash = read_until_newline(&newline, &stash, fd);
	}
	if(newline)
	{
		line = ft_substr(stash, 0 , (newline - stash) + 1);
		if(newline[1])
		{
			temp = ft_substr(newline, 1, ft_strlen(newline) - 1);
			free(stash);
			stash = temp;
		}
		else
		{
			free(stash);
			stash = NULL;
		}
	}
	else
	{
		line = ft_strdup(stash);
		free(stash);
		stash = NULL;
	}
	if (*line == '\0')
	{
		free(line);
		return(NULL);
	}
	return (line);
}

// int main()
// {
// 	char *str;
// 	int fd;
// 	int i = 0;
// 	fd = open("testfile.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("failed to open");
// 		return (1);
// 	}
// 	while(i < 12)
// 	{
// 		str = get_next_line(fd);
// 		printf("%s", str);
// 		free(str);
// 		str = NULL;
// 		i++;
// 	}
// 	close(fd);
// 	return 0;
// }
