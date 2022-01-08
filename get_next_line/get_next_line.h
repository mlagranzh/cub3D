#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		get_next_line(int fd, char **line);
size_t	ft_strlen (const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char *s);
int error(char *buf, char *ostatok);