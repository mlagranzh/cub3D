#include "cub3d.h"

size_t len_int(int *array)
{
	size_t	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array)
	{
		i++;
		array++;
	}
	return (i);
}

int search_in_array(int *array, int search)
{
	size_t len = len_int(array);
	size_t i = -1;

	while (++i < len)
	{
		if (search == array[i])
			return (i);
	}
	return (-1);
}


int *add_to_dict(int *array, int number)
{
	size_t malloc_size;

	malloc_size = len_int(array);
	if (malloc_size == 0)
		malloc_size = 1;
	array = malloc(sizeof(int) * malloc_size + 1);
	array[len_int(array)] = number;
	return (array);
}

int *create_dictionary(int **array)
{
	int count_uniq_color;
	int x = -1;
	int y = -1;
	int z = -1;
	int *dict;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			if (search_in_array(dict, array[x][y]) == -1)
				dict = add_to_dict(dict, array[x][y]);
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

	    file = fopen("fprintf.txt", "w");
		int i = -1;
		while (++i < len_int(dict))
		{
			fprintf(file, "\"%c c #%s\n\"", i, ft_itoa_base(dict[i],16)); 
		}
		fprintf(file, "/* pixels */\n");
		int x = -1;
		int y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			x = -1;
			while (++x < SCREEN_WIDTH)
			{
				fprintf(file, "%c", search_in_array(dict, array[x][y]));
			}
			fprintf(file, "\n");
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
		// int *dict = create_dictionary();
		// create_file(dict);
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
