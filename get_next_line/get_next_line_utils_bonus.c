#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str != '\0' && *str != '\n')
	{
		i++;
		str++;
	}
	return (i);
}

void	*gnl_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*object;

	object = malloc(count * size);
	if (object == NULL)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		object[i] = 0;
		i++;
	}
	return (object);
}

char	*gnl_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

t_list	*gnl_new_list(int fd)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->fd = fd;
	list->static_line = NULL;
	list->next = NULL;
	return (list);
}

int	gnl_strjoin(const char **line, const char *static_line)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	new_str = (char *)malloc(gnl_strlen(*line) + gnl_strlen(static_line) + 1);
	if (new_str == NULL)
		return (-1);
	while (line[0][i] != '\0')
	{
		new_str[i] = line[0][i];
		i++;
	}
	j = 0;
	while (static_line[j] != '\0' && static_line[j] != '\n')
	{
		new_str[i] = static_line[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	free ((char *)*line);
	*line = new_str;
	return (1);
}
