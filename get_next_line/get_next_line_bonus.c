#include "get_next_line_bonus.h"

int	gnl_tail_cutting(char **str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 1;
	while (str[0][i - 1] != '\n')
		i++;
	tmp = (char *)gnl_calloc(BUFFER_SIZE + 1, 1);
	if (tmp == NULL)
		return (-1);
	j = 0;
	while (str[0][i] != '\0')
	{
		tmp[j] = str[0][i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free (*str);
	*str = tmp;
	return (1);
}

int	gnl_get_line(int fd, char **line, char **static_line)
{
	int	sumbol_read;

	sumbol_read = 1;
	*line = (char *)gnl_calloc(sizeof(char), 1);
	if (*static_line == NULL)
		*static_line = (char *)gnl_calloc(BUFFER_SIZE + 1, 1);
	while (*static_line != NULL && *line != NULL && sumbol_read != 0)
	{
		if (gnl_strjoin((const char **)line, *static_line) != -1)
			if (gnl_strchr(*static_line, '\n'))
				return (gnl_tail_cutting(static_line));
		sumbol_read = read(fd, *static_line, BUFFER_SIZE);
		if (sumbol_read < 0)
			return (-1);
		static_line[0][sumbol_read] = '\0';
	}
	if (sumbol_read == 0)
		return (0);
	return (-1);
}

void	gnl_free_list_util(t_list *list, int fd)
{
	t_list	*l_left;
	t_list	*l_right;
	int		a;

	a = 1;
	l_left = list;
	while (l_left->next != NULL && a == 1)
	{
		l_right = l_left->next;
		if (l_right->fd == fd)
		{
			if (l_right->static_line)
				free (l_right->static_line);
			l_right = l_right->next;
			free(l_left->next);
			l_left->next = l_right;
			a = 0;
		}
		else
			l_left = l_left->next;
	}	
}

t_list	*gnl_free_list(t_list *list, t_list *tmp)
{
	if (tmp == list)
	{
		if (list->next != NULL)
		{
			list = list->next;
			if (list->static_line)
				free (tmp->static_line);
			free (tmp);
		}
		else
		{
			if (list->static_line)
				free (tmp->static_line);
			free (tmp);
			list = NULL;
		}
	}
	else
		gnl_free_list_util(tmp, tmp->fd);
	return (list);
}

int	get_next_line(int fd, char **line)
{
	static t_list	*list;
	t_list			*tmp;
	int				retval;

	if (fd < 0 || line == 0 || fd > 100)
		return (-1);
	if (list == NULL)
		list = gnl_new_list(fd);
	if (list == NULL)
		return (-1);
	tmp = list;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = gnl_new_list(fd);
		if (tmp->next == NULL)
			return (-1);
		tmp = tmp->next;
	}
	retval = gnl_get_line(fd, line, &tmp->static_line);
	if (retval <= 0)
		list = gnl_free_list(list, tmp);
	return (retval);
}
