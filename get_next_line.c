/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:17:46 by phartman          #+#    #+#             */
/*   Updated: 2024/05/06 18:29:35 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	char buf[20];
	size_t size;
	size_t size_read;
	size_t total_read;

	total_read = 0;

	while(size_read != -1 && buf[total_read] != '\n')
	{
		size_read = read(fd, buf, 1);
		total_read++;
	}
	return (buf);
}

int main(int argc, char const *argv[])
{
	char *str;
	str = get_next_line(open("testfile.txt"));
	printf("%s", str);
	return 0;
}
