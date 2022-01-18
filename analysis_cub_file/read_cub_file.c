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

typedef struct s_map_list
{
	char *line;
	struct s_map_list *next;
}	t_map_list;

void	print_map_param(t_map *map)
{
	printf("no = {%s}\n", map->no_texture);
	printf("so = {%s}\n", map->so_texture);
	printf("we = {%s}\n", map->we_texture);
	printf("ea = {%s}\n", map->ea_texture);
	printf("fl = %i\n", map->floor_color);
	printf("ce = %i\n", map->ceilling_color);
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

	while(mas && mas[i])
	{
		printf("{%s}\n", mas[i]);
		i++;
	}
	// printf("%s\n", mas[i]);
}

char **make_map(int fd)
{
	char *line;
	t_map_list *map_list;
	t_map_list *first_map_list;
	int line_num;
	int	max_line_len;
	char **map;
	int retval;
	int i;
	int j;

	map = NULL;
	map_list = (t_map_list *)malloc(sizeof(t_map_list));
	first_map_list = map_list;
	line_num = 0;
	max_line_len = 0;
	while (1)
	{
		i = 0;
		line = NULL;
        retval = get_next_line(fd, &line);
		if (retval == -1 || !line)
			return (NULL);
		while (line[i] == ' ' || line[i] == '\t')
			i++;
        if (line[i] == '\0' || line[i] == '\n')
		{
			if (retval == 0 || line_num != 0)// || map != NULL)
				break ;
            continue ;
		}
		line_num++;
		if (max_line_len < ft_strlen(line))
			max_line_len = ft_strlen(line);
		map_list->line = line;
		map_list->next = (t_map_list *)malloc(sizeof(t_map_list));
		map_list = map_list->next;
		// map = ft_realloc(map, line);
		if (retval == 0)
            break ;
	}
    if (line_num == 0)
        return (NULL);
	map = (char **)malloc(sizeof(char *) * (line_num + 1));
	map[line_num] = NULL;
	i = 0;
	while (i < line_num)
	{
		map[i] = (char *)malloc(sizeof(char) * (max_line_len + 1));
		map[i][max_line_len] = '\0';
		j = 0;
		while (j < ft_strlen(first_map_list->line))
		{
			map[i][j] = first_map_list->line[j];
			j++;
		}
		while (j < max_line_len)
		{
			map[i][j] = ' ';
			j++;
		}
		first_map_list = first_map_list->next;
		i++;
	}
	return (map);
}

int checking_map_for_invalid_sumbol(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0') // N,S,E or W
		{
			if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W')
				return (ERROR);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int search_player_pos_in_map(char **map, t_player *player)
{
	int	pos_num;
	int i;
	int j;

	pos_num = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				player->pos_x = i;
				player->pos_y = j;
				pos_num++;
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (pos_num != 1)
		return (ERROR);
	return (SUCCESS);
}

int	read_map(t_map *map, t_player *player, int fd)
{
	map->map = make_map(fd);
	if (!map->map)
		return (ERROR);
	if (checking_map_for_closure(map->map) == ERROR
		|| checking_map_for_invalid_sumbol(map->map) == ERROR
		|| search_player_pos_in_map(map->map, player) == ERROR)
		return (ERROR);
	return (SUCCESS);
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

void	initialize_map(t_map *map)
{
	map->ea_texture = NULL;
	map->map = NULL;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
}

int	read_cub_file(t_map *map, t_player *player, char *file_name)
{
	int fd;

	initialize_map(map);
	if (check_for_file_permission(file_name) == ERROR)
		return (print_return(ERROR, "File permission is invalid"));
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (print_return(ERROR, "File open error"));
	if (read_map_param(map, fd) == ERROR)
		return (print_return(ERROR, "Map param in file error"));
	if (read_map(map, player, fd) == ERROR)
		return (print_return(ERROR, "Map field error"));
	return (SUCCESS);
}

// int main(int argc, char **argv)
// {
// 	t_map		map;
// 	t_player	player;
    
// 	if (argc == 1)
// 		return (0);
// 	initialize_map(&map);
// 	if (read_cub_file(&map, &player, argv[1]) == SUCCESS)
// 	{
// 		// print_map_param(&map);
// 		ft_print_cchar(map.map);
// 	}
//     return (0);
// }
