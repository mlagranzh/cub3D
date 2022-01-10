#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
// #include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		get_next_line(int fd, char **line);
size_t	gnl_strlen (const char *str);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
size_t	gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_strdup(char *s);
int error(char *buf, char *ostatok);

#endif