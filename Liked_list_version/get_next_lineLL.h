#ifndef GET_NEXT_LINELL_H
# define GET_NEXT_LINELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 15
#endif
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;


int	ft_lstsize(t_list *lst);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
void list_clear(t_list **head);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char *get_next_line(int fd);

#endif
