#include "../cub3d.h"

char **ft_realloc(char **mas, char *new_line)
{
	char **new_mas;
	int mas_len;
	int i;

	if (!mas)
	{
		mas_len = 2;
		new_mas = (char **)malloc(sizeof(char *) * mas_len);
		new_mas[0] = new_line;
		new_mas[1] = NULL;
	}
	else
	{
		mas_len = 0;
		while (mas && mas[mas_len])
			mas_len++;
		mas_len++;
		new_mas = (char **)malloc(sizeof(char *) * (mas_len + 1));
		i = -1;
		while (++i < mas_len - 1)
			new_mas[i] = mas[i];
		new_mas[i] = new_line;
		new_mas[i + 1] = NULL;
		free (mas);
	}
	return (new_mas);
}

void	ft_print_cchar(char **mas)
{
	int i = 0;

	while(mas[i])
	{
		printf("%s\n", mas[i]);
		i++;
	}
	// printf("%s\n", mas[i]);
}

char **make_map(char *file_name)
{
	char *line;
	char **map;
	int fd;
	int retval;

    line = NULL;
	map = NULL;
	fd = open(file_name, O_RDONLY);
    if (fd == -1)
        return (NULL);
	while (1)
	{
        retval = get_next_line(fd, &line);
        if (line == NULL || *line == '\0')
            break ;
		map = ft_realloc(map, line);
		if (retval <= 0)
            break ;
	}
    if (!map || !*map)
        return (NULL);
	ft_print_cchar(map);
	return (map);
}

int main()
{
    make_map("map.cub");
    return (0);
}