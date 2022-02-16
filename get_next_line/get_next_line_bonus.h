#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include			<stdio.h>
# include			<stdlib.h>
# include			<fcntl.h>
# include			<unistd.h>

# define BUFFER_SIZE 10

typedef struct s_list
{
	char			*static_line;
	int				fd;
	struct s_list	*next;
}					t_list;

t_list				*gnl_free_list(t_list *list, t_list *tmp);
t_list				*gnl_new_list(int fd);
size_t				gnl_strlen(const char *str);
void				gnl_free_list_util(t_list *list, int fd);
void				*gnl_calloc(size_t count, size_t size);
char				*gnl_strchr(char *s, int c);
int					gnl_strjoin(const char **line, const char *static_line);
int					gnl_get_line(int fd, char **line, char **static_line);
int					get_next_line(int fd, char **line);
int					gnl_tail_cutting(char **str);

#endif