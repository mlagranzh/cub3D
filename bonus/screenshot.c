#include "../cub3d.h"

int	search_in_array(int *array, int search)
{
	int	i;

	i = -1;
	if (array == NULL)
		return (-1);
	while (array[++i] != -1)
	{
		if (search == array[i])
			return (i);
	}
	return (-1);
}

int	*add_to_dict(int *array, int number)
{
	int		*new_array;
	int		i;

	new_array = malloc(sizeof(int) * len_int(array) + 5);
	i = -1;
	if (array != NULL)
	{
		while (array[++i] != -1)
			new_array[i] = array[i];
	}
	else
		++i;
	new_array[i] = number;
	new_array[i + 1] = -1;
	free(array);
	return (new_array);
}

int	*create_dictionary(int **array)
{
	int	*dict;
	int	x;
	int	y;

	dict = NULL;
	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			if (search_in_array(dict, array[y][x]) == -1)
				dict = add_to_dict(dict, array[y][x]);
		}
	}
	return (dict);
}

static void	print_pixels(FILE *file, int *dict, int **map)
{
	int	x;
	int	y;

	y = -1;
	fprintf(file, "/* pixels */\n");
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		fprintf(file, "\"");
		while (++x < SCREEN_WIDTH)
		{
			fprintf(file, "%c", search_in_array(dict, map[y][x]) + 35);
		}
		fprintf(file, "\",\n");
	}
}

void	create_file(FILE *file, int *dict, int **map)
{
	int		i;
	char	*color;

	fprintf(file, "\"%d %d %d %d\",\n", SCREEN_WIDTH, \
					SCREEN_HEIGHT, len_int(dict), 1);
	i = -1;
	while (++i < len_int(dict))
	{
		color = ft_itoa_base(dict[i], 16);
		fprintf(file, "\"%c c #%s\",\n", i + 35, color);
		free(color);
	}
	print_pixels(file, dict, map);
}

void	shot(t_all *all)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(&all->img, x, y, 0x4d4a4a);
	}
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
}

static int	**create_color_map(t_data *img)
{
	int	i;
	int	**array;
	int	x;
	int	y;

	i = -1;
	array = malloc(sizeof(int *) * SCREEN_HEIGHT);
	while (++i < SCREEN_HEIGHT)
		array[i] = malloc(sizeof(int) * SCREEN_WIDTH);
	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			array[y][x] = my_mlx_pixel_get(img, x, y);
		}
	}
	return (array);
}

static FILE	*open_file()
{
	static int	num = 0;
	char		*num_shots;
	char		*name_screenshot;
	FILE		*file;

	num_shots = ft_itoa(num);
	name_screenshot = my_strjoin("screenshot/screenshot", num_shots, ".xpm");
	file = fopen(name_screenshot, "w");
	num++;
	free(num_shots);
	free(name_screenshot);
	return (file);
}

void	screenshot(t_all *all)
{
	int			**color_map;
	int			*dict;

	color_map = create_color_map(&all->img);
	dict = create_dictionary(color_map);
	create_file(open_file(), dict, color_map);
	shot(all);
	free_2d_int(color_map, SCREEN_HEIGHT);
	free(dict);
}
