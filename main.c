#include "cub3d.h"

void cub_init(t_all *all)
{
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub");
	all->img.img = mlx_new_image(all->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);
	all->player.dir_x = 0;
	all->player.dir_y = 1;
	all->player.plane_x = 1;
	all->player.plane_y = 0.66;//2D-лучевая версия плоскости камеры
	all->player.moveSpeed = 0.3;
	all->player.rotSpeed = 0.3;
	texture_load(all, all->map.no_texture);
	texture_load(all, all->map.so_texture);
	texture_load(all, all->map.we_texture);
	texture_load(all, all->map.ea_texture);
}

int main(int argc, char **argv)
{
	t_all	all;
	char	*file_name;

	file_name = "maps/map.cub";
	if (argc == 2)
		file_name = argv[1];
	if (read_cub_file(&all.map, &all.player, file_name) != SUCCESS)
		return (1);
	cub_init(&all);

	// draw_screen(&all);

	// draw_map(&all.img, all.map.map);
	// draw_player(&all);
	// mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	mlx_hook(all.win, 2, 1L << 2, my_hook, (void *)&all);
	mlx_hook(all.win, 17, 0L, destroy, (void *)&all);

	mlx_loop(all.mlx);
	return (0);
}