#include "cub_file.h"

int	str_empty(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		return (TRUE);
	return (FALSE);
}

char *skip_space(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

int	free_data(void *data, int retval)
{
	if (data)
		free (data);
	return (retval);
}

t_map_mas	initial_map_list(void)
{
	t_map_mas	map_list;

	map_list.first_line = (t_line_list *)malloc(sizeof(t_line_list));
	if (map_list.first_line)
	{
		map_list.first_line->next = NULL;
		map_list.line = map_list.first_line;
		map_list.line_num = 0;
		map_list.max_line_len = 0;
	}
	else
		map_list.line_num = -1;
	return (map_list);
}

int	free_map_list(t_map_mas map_list, int retval)
{
	while (map_list.first_line)
	{
		map_list.line = map_list.first_line->next;
		free (map_list.first_line);
		map_list.first_line = map_list.line;
	}
	return (retval);
}
