#include "../cub3d.h"

void	printf_array_int(int *arr, int size)
{
	int i = -1;

	while (++i < size)
		printf("%d\n", arr[i]);
}

int len_int(int *array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != -1)
		i++;
	return (i);
}

int search_in_array(int *array, int search)
{
	int i = -1;

	if (array == NULL)
		return -1;
	while (array[++i] != -1)
	{
		if (search == array[i])
			return (i);
	}
	return (-1);
}


int *add_to_dict(int *array, int number)
{
	int	*new_array;
    int i;

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

int *create_dictionary(int **array)
{
	int count_uniq_color;
	int x = -1;
	int y = -1;


	int *dict;
	dict = NULL;

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

int		ft_itoa_base_count(unsigned long int nb, unsigned int base)
{
	int i;

	if (nb == 0)
		return (1);
	i = 0;
	while (nb)
	{
		nb = nb / base;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(unsigned long int nb, unsigned int base)
{
	char	*ret;
	char	*numbers;
	int		size;

	numbers = ft_strdup("0123456789abcdef");
	ret = NULL;
	size = ft_itoa_base_count(nb, base);
	if (!(ret = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ret[size--] = '\0';
	while (size >= 0)
	{
		ret[size--] = numbers[nb % base];
		nb /= base;
	}
	free(numbers);
	return (ret);
}


void create_file(int *dict, int **array)
{
	FILE *file;
	static int num = 0;

	char *num_screenshot = ft_itoa(num);
	char *name_screenshot = my_strjoin("screenshot/screenshot", num_screenshot, ".xpm");
	num++;
	file = fopen(name_screenshot, "w");
	fprintf(file, "\"%d %d %d %d\",\n", SCREEN_WIDTH, SCREEN_HEIGHT, len_int(dict), 1);
	int i = -1;
	while (++i < len_int(dict))
	{
		fprintf(file, "\"%c c #%s\",\n", i + 35, ft_itoa_base(dict[i],16)); 
	}
	fprintf(file, "/* pixels */\n");
	int x = -1;
	int y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		fprintf(file, "\"");
		while (++x < SCREEN_WIDTH)
		{
			fprintf(file, "%c", search_in_array(dict, array[y][x]) + 35);
		}
		fprintf(file, "\",\n");
	}
	free(num_screenshot);
	free(name_screenshot);
}

//why not work???!?!?
void shot(t_all *all)
{
	int x;
	int y;
	
	y = -1;
	x = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
            my_mlx_pixel_put(all->img.img, x, y, 0);
		}
	}
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
}

static int **create_color_map(t_data *img)
{
	int i;
	int **array;

	i = -1;
	array = malloc(sizeof(int *) * SCREEN_HEIGHT);
	while (++i < SCREEN_WIDTH)
		array[i] = malloc(sizeof(int) * SCREEN_WIDTH);
	int x = -1;
	int y = -1;
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
void screenshot(t_all *all)
{
	int **color_map;
	int *dict;

	color_map = create_color_map(&all->img);
	dict = create_dictionary(color_map);
	create_file(dict, color_map);
	shot(all);
	free_2d_int(color_map, SCREEN_HEIGHT);
	free(dict);
}

