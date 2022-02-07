#include "cub3d.h"

void sprites_init(t_all *all)
{
	t_data data;

    data.img = mlx_xpm_file_to_image(all->mlx, "textures/barrel.xpm", &data.line_length, &data.line_length);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	t_sprite sprites[SPRITES_NUM] =
    {
        {1.5, 19.5, 70, 0, &data},
        // {2.0, 4.0, &data},
        // {3.0, 3.0, &data},
        // {4.0, 2.0, &data},
        // {5.0, 1.0, &data}
    };

	
}

void side_init(t_player *player)
{
	if (player->start_side == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	if (player->start_side == 'N')
	{
		player->dir_x = 0.210796;
		player->dir_y = -0.977530;
		player->plane_x = -0.645170;
		player->plane_y = -0.139125;
	}
	if (player->start_side == 'E')
	{
		player->dir_x = 0.989992;
		player->dir_y = 0.141120;
		player->plane_x = 0.093139;
		player->plane_y = -0.653395;
	}
	if (player->start_side == 'S')
	{
		player->dir_x = 0.227202;
		player->dir_y = 0.973848;
		player->plane_x = 0.642739;
		player->plane_y = -0.149953;
	}
}

void cub_init(t_all *all)
{
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub");
	all->img.img = mlx_new_image(all->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);
	
	side_init(&all->player);

	all->player.moveSpeed = 0.3;
	all->player.rotSpeed = 0.3;
	texture_load(all, all->map.no_texture);
	texture_load(all, all->map.so_texture);
	texture_load(all, all->map.we_texture);
	texture_load(all, all->map.ea_texture);

	all->z_buffer = (int *)malloc(sizeof(int) * SCREEN_WIDTH);
}

int mouse_hook(int x, int y, t_all *all)
{
	double oldDir;
	double oldPlane;
	double rotSpeed;

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
	return (0);
}

int draw_all(t_all *all)
{
	static int i = 0;

	if (i > 70)
		i = 1;
	all->img.img = mlx_new_image(all->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);

	draw_screen(all);
	draw_border_centre_square(&all->img, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 0xFFFFFF, 0x000000);
	draw_minimap(all);
	// draw_sprites(all, i++);

	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (0);
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

	mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	mlx_hook(all.win, 2, 1L << 2, my_hook, (void *)&all);
	mlx_hook(all.win, 17, 0L, destroy, (void *)&all);
	mlx_hook(all.win, 6, 0, mouse_hook, (void *)&all);

	mlx_loop_hook(all.mlx, draw_all, (void *)&all);

	mlx_loop(all.mlx);
	return (0);
}
