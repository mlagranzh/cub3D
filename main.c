#include "cub3d.h"

char **make_map_0(char *file_name)
{
	char *line;
	char **map;
	int fd;
	int i;

	fd = open(file_name, O_RDONLY);
	line = NULL;
	map = NULL;
	i = 1;
	while (get_next_line(fd, &line) == 1)
	{
		map = ft_realloc(map, delete_space_line(line));
		i++;
	}
	map = ft_realloc(map, delete_space_line(line));
	// ft_print_cchar(map);
	return (map);
}

time_t programstart;

int main()
{
	t_all	all;

	all.mlx = mlx_init();
	all.map = make_map_0("map.cub");
	// printf_array(all.map);
	all.win = mlx_new_window(all.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub");
	all.img.img = mlx_new_image(all.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	all.img.addr = mlx_get_data_addr(all.img.img, &all.img.bits_per_pixel, &all.img.line_length, &all.img.endian);

	all.player.pos_x = 7;
	all.player.pos_y = 12;
	all.player.dir_x = 0;
	all.player.dir_y = 1;
	all.player.plane_x = 1;
	all.player.plane_y = 0.66;//2D-лучевая версия плоскости камеры
	time(&programstart);
	all.player.time = 0;

	draw_screen(&all);

	
	draw_map(&all.img, all.map);
	draw_player(&all);
	mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	mlx_hook(all.win, 2, 1L << 2, my_hook, (void *)&all);
	mlx_hook(all.win, 17, 0L, destroy, (void *)&all);

	mlx_loop(all.mlx);
	return (0);
}