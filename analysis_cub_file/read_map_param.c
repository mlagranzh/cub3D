#include "../cub3d.h"

static int	check_param_key(char *key)
{
	int i;

	i = 0;
	if (!ft_isalpha(key[i++]))
		return (ERROR);
	if (ft_isalpha(key[i]))
		i++;
	if (key[i] != '\0')
		return (ERROR);
	return (SUCCESS);
}

static int	check_color_param(char *param)
{
	if (!ft_isdigit(*param))
		return (ERROR);
	while (ft_isdigit(*param))
		param++;
	if (*param != ',')
		return (ERROR);
	param++;
	if (!ft_isdigit(*param))
		return (ERROR);
	while (ft_isdigit(*param))
		param++;
	if (*param != ',')
		return (ERROR);
	param++;
	if (!ft_isdigit(*param))
		return (ERROR);
	while (ft_isdigit(*param))
		param++;
	if (*param != '\0')
		return (ERROR);
	return (SUCCESS);
}

static int	write_color_param(t_map *map, char *param, char key)
{
	char **param_mas;

	param_mas = ft_split(param, ',');
	if (!param_mas)
		return (ERROR);
	if (key == 'F')
		map->floor_color = create_trgb(0, ft_atoi(param_mas[0]), \
						ft_atoi(param_mas[1]), ft_atoi(param_mas[2]));
	if (key == 'C')
		map->ceilling_color = create_trgb(0, ft_atoi(param_mas[0]), \
						ft_atoi(param_mas[1]), ft_atoi(param_mas[2]));
	return (SUCCESS);
}

static int	write_map_param(t_map *map, char **param)
{
	if (param == NULL || *param == NULL || *(param + 1) == NULL || *(param + 2) != NULL)
		return (ERROR);
	if (check_param_key(param[0]) == ERROR)
		return (ERROR);
	if (param[0][0] == 'N' && param[0][1] == 'O' && param[0][2] == '\0')
		map->no_texture = param[1];
	else if (param[0][0] == 'S' && param[0][1] == 'O' && param[0][2] == '\0')
		map->so_texture = param[1];
	else if (param[0][0] == 'W' && param[0][1] == 'E' && param[0][2] == '\0')
		map->we_texture = param[1];
	else if (param[0][0] == 'E' && param[0][1] == 'A' && param[0][2] == '\0')
		map->ea_texture = param[1];
	else if ((param[0][0] == 'F' || param[0][0] == 'C') && param[0][1] == '\0'
		&& check_color_param(param[1]) == SUCCESS
		&& write_color_param(map, param[1], param[0][0]) == SUCCESS)
		return (SUCCESS);
	else
		return (ERROR);
	return (SUCCESS);
}

int	read_map_param(t_map *map, int fd)
{
	char	*line;
	char	**param;
	int		retval;
	int		i;
	int		reads_param_num;

	line = NULL;
	reads_param_num = 0;
	while (1)
	{
		retval = get_next_line(fd, &line);
		if (retval == -1 || !line)
			return (ERROR);
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0' || line[i] == '\n')
		{
			if (retval == 0)
				break ;
			continue ;
		}
		reads_param_num++;
		ft_change_sumbols_in_str(line, "\t", ' ');
		param = ft_split(line, ' ');
		if (!param || write_map_param(map, param) == ERROR)
			return (ERROR);
		if (retval == 0 || reads_param_num == 6)
			break ;
	}
	if (reads_param_num != 6)
		return (ERROR);
	return (SUCCESS);
}
