#include "cub3d.h"

time_t programstart;

int main(int argc, char **argv)
{
	t_all	all;
	char	*file_name;

	file_name = "maps/map.cub";
	if (argc == 2)
		file_name = argv[1];
	if (read_cub_file(&all.map, &all.player, file_name) != SUCCESS)
		return (1);
	ft_print_cchar(all.map.map);
	all.mlx = mlx_init();
	all.win = mlx_new_window(all.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub");
	all.img.img = mlx_new_image(all.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	all.img.addr = mlx_get_data_addr(all.img.img, &all.img.bits_per_pixel, &all.img.line_length, &all.img.endian);

	all.player.dir_x = -1;
	all.player.dir_y = 0;
	all.player.plane_x = 1;
	all.player.plane_y = 0.66;//2D-лучевая версия плоскости камеры
	time(&programstart);
	all.player.time = 0;

	// draw_screen(&all);

	
	draw_map(&all.img, all.map.map);
	draw_player(&all);
	mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	mlx_hook(all.win, 2, 1L << 2, my_hook, (void *)&all);
	mlx_hook(all.win, 17, 0L, destroy, (void *)&all);

	mlx_loop(all.mlx);
	return (0);
}