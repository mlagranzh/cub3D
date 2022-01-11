#include "../cub3d.h"

/*
   
   NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0

North South West East
Север Юг Запад Восток
*/

typedef struct s_map
{
	char	*no_texture; 		// Север	(90)
	char	*so_texture; 		// Юг 		(270)
	char	*we_texture; 		// Запад 	(180)
	char	*ea_texture; 		// Восток 	(0)
	char	*floor_color; 		// Пол
	char	*ceilling_color;	// Потолок
	char	**map;
}	t_map;

// typedef struct	s_player
// {
// 	int		pos_x;				// Позиция по х
// 	int		pos_y;				// Позиция по у
// 	int		dir_x;				// Направление по х
// 	int		dir_y;				// Направление по у
// }	t_player;

int		print_return(int retval, char *print_message)
{
	printf("%s", print_message);
	return (retval);
}

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

int	check_for_file_permission(char *file_name)
{
	char	*permission;
	int		counter;

	permission = ".cub";
	counter = 0;
	while (*file_name)
	{
		if (*file_name != permission[counter])
			counter = 0;
		if (*file_name == permission[counter])
			counter++;
		file_name++;
	}
	if (counter == 4)
		return (SUCCESS);
	return (ERROR);
}

void	change_sumbols_in_str(char *change_str, char *change_sumbols, char replacement_char)
{
	int i;

	i = 0;
	while (str && *str)
	{
		while (change_sumbols[i] != '\0')
		{
			if (change_sumbols[i] == *str)
				*str = replacement_char;
			i++;
		}
		str++;
	}
}



int	read_map_param(t_map *map, int fd)
{
	char	*line;
	char	**buf;
	char	*mark;
	char	*permission;
	int		i;

	line = NULL;
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (!line)
			return (ERROR);
		if (*line == '\0')
			continue ;
		change_sumbols_in_str(line, "\t", ' ');
		buf = ft_split(line, ' ');

	}
}

int	read_cub_file(t_map *map, t_player *player, char *file_name)
{
	int fd;

	if (check_for_file_permission(file_name) == ERROR)
		return (print_return(ERROR, "File permission is invalid"));
	// read_map_param(map, fd);
	// read_map(map, player, fd);
	return (0);
}

void	initialize_map(t_map *map)
{
	
}

int main(int argc, char **argv)
{
	t_map		map;
	t_player	player;
    

	printf("{%s}\n", ft_strtrim(" 1     2   3    ", " 	"));
    return (0);
}