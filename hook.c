#include "cub3d.h"

void printf_array_int(int *arr, int size)
{
	int i = -1;

	while (++i < size)
		printf("%d\n", arr[i]);
}

int len_int(int *array)
{
	int	i;

	i = -1;
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

	new_array = malloc(sizeof(int) * len_int(array) + 3282838);

	int i = -1;
	if (array != NULL)
	{
		while (array[++i] != -1)
			new_array[i] = array[i];
	}
	else
		++i;
	new_array[i] = number;
	new_array[i + 1] = -1;
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

	    file = fopen("screenshot.xpm", "w");
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
}

int		my_hook(int key, t_all *all)
{
	if (key == KEY_W || key == KEY_S)
		move_straight(key, all);
	if (key == KEY_A || key == KEY_D)
		move_side(key, all);
	if (key == KEY_LEFT)
		rotate(key, all);
	if (key == KEY_RIGHT)
		rotate(key, all);
	if (key == KEY_ESC)
		exit(0);
	if (key == 49)
	{
		if (all->sprites.coller_min == 0)
		{
			all->sprites.coller_min = all->sprites.coller_max;
			all->sprites.coller = all->sprites.coller_max;
			all->sprites.coller_mod = 30;
		}
		else
		{
			all->sprites.coller_min = 0;
			all->sprites.coller = 0;
			all->sprites.coller_mod = 45;
		}
	}
    if (key == 36) 
		fog(all);
	if (key == 111)
	{
		int **array = malloc(sizeof(int *) * SCREEN_HEIGHT);
		int i = -1;
		while (++i < SCREEN_WIDTH)
			array[i] = malloc(sizeof(int) * SCREEN_WIDTH);
		int x = -1; int y = -1;

		while (++y < SCREEN_HEIGHT)
		{
			x = -1;
			while (++x < SCREEN_WIDTH)
			{
				array[y][x] = my_mlx_pixel_get(&all->img, x, y);
			}
		}
		int *dict = create_dictionary(array);
		// printf_array_int(dict, 20);
		create_file(dict, array);
	}
 	if (key == 13 || key == 1 || key == 0 || key == 2 || key == 123 || key == 124 || key == 49 || key == 36)
	{
		draw_screen(all);		
		draw_sprites(all);
		draw_minimap(all);
		mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	}

	return (0);
}

int mouse_hook(int x, int y, t_all *all)
{
	double oldDir;
	double oldPlane;
	double rotSpeed;
	mlx_mouse_hide();

	if (x < 0 || x > SCREEN_WIDTH)
		mlx_mouse_move(all->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	if (x != all->x)
	{
		rotSpeed = 0.03;
		if (x > all->x)
			rotSpeed = -rotSpeed;

		oldDir = all->player.dir_x;
		all->player.dir_x = all->player.dir_x * cos(rotSpeed) - all->player.dir_y * sin(rotSpeed);
		all->player.dir_y = oldDir * sin(rotSpeed) + all->player.dir_y * cos(rotSpeed);
		oldPlane = all -> player.plane_x;
		all -> player.plane_x = all -> player.plane_x * cos(rotSpeed) - all -> player.plane_y * sin(rotSpeed);
		all -> player.plane_y = oldPlane * sin(rotSpeed) + all -> player.plane_y * cos(rotSpeed);
	}
	all -> x = x;
	draw_screen(all);
	draw_sprites(all);
	draw_minimap(all);

	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (0);
}

int loop_hook(t_all *all)
{
	draw_sprites(all);
    draw_minimap(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (0);
}
