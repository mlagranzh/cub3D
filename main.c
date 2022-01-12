#include "cub3d.h"

// char **make_map(char *file_name)
// {
// 	char *line;
// 	char **map;
// 	int fd;
// 	int i;

// 	fd = open(file_name, O_RDONLY);
// 	line = NULL;
// 	map = NULL;
// 	i = 1;
// 	while (get_next_line(fd, &line) == 1)
// 	{
// 		map = ft_realloc(map, delete_space_line(line));
// 		i++;
// 	}
// 	map = ft_realloc(map, delete_space_line(line));
// 	// ft_print_cchar(map);
// 	return (map);
// }

void	draw_square(t_data *img, int y, int x, int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, x * size + i, y * size + j, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *img, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0')
				draw_square(img, i, j, CEL_SIZE);
			j++;
		}
		i++;
	}
}

// void	draw_player(t_all *all)
// {
// 	int i;
// 	int j;
// 	int size;

// 	i = 0;
// 	size = 4;
// 	while (i < size)
// 	{
// 		j = 0;
// 		while (j < size)
// 		{
// 			my_mlx_pixel_put(&(all->img), all->player.x + i, all->player.y + j, 0xFF00FF);
// 			j++;
// 		}
// 		i++;
// 	}
// 	float player_a = 0;
// 	float start = player_a - 3.14/4;
// 	float end = player_a + 3.14/4;
// 	while (start < end)
// 	{
// 		float x_2 = all->player.x;
// 		float y_2 = all->player.y;
// 		while (all->map[(int)(y_2/CEL_SIZE)][(int)(x_2/CEL_SIZE)] != '1')
// 		{
// 			x_2 += cos(start);
// 			y_2 += sin(start);
// 			my_mlx_pixel_put(&all->img, x_2, y_2, 0xFF00FF);
// 		}
// 		//Рассчитываем высоту линии для рисования на экране
//       	int line_height = (int)(SCREEN_HEIGHT / (y_2 - all->player.y));

// 		start += 3.14/20;
// 	}
// }

int main()
{
	t_all	all;

	all.mlx = mlx_init();
	// all.map = make_map("map.cub");
	// printf_array(all.map);
	all.win = mlx_new_window(all.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub");
	all.img.img = mlx_new_image(all.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	all.img.addr = mlx_get_data_addr(all.img.img, &all.img.bits_per_pixel, &all.img.line_length, &all.img.endian);

	all.pos_x = 7;
	all.pos_y = 12;
	all.dir_x = 0;
	all.dir_y = 1;
	all.plane_x = 1;
	all.plane_y = 0.66;//2D-лучевая версия плоскости камеры
	
	draw_screen(&all);

	
	draw_map(&all.img, all.map);
	draw_player(&all);
	mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	mlx_hook(all.win, 2, 1L << 2, my_hook, (void *)&all);
	mlx_hook(all.win, 17, 0L, destroy, (void *)&all);

	mlx_loop(all.mlx);
	return (0);
}