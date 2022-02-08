#include "cub3d.h"

void sprites_init(t_all *all)
{
	all->sprites.num = 2;

	all->sprites.z_buffer = (int *)malloc(sizeof(int) * SCREEN_WIDTH);

	all->sprites.coordinates = (t_coordinate *)malloc(sizeof(t_coordinate) * all->sprites.num);

	all->sprites.coordinates[0].texture = (t_data *)malloc(sizeof(t_data) * 2);
	texture_load(all, &all->sprites.coordinates[0].texture[0], "textures/barrel_whole.xpm");
	texture_load(all, &all->sprites.coordinates[0].texture[1], "textures/barrel_ruined.xpm");
	
	all->sprites.coordinates[1].texture = (t_data *)malloc(sizeof(t_data) * 3);
	texture_load(all, &all->sprites.coordinates[1].texture[0], "textures/ellowlight.xpm");
	texture_load(all, &all->sprites.coordinates[1].texture[1], "textures/redlight.xpm");
	texture_load(all, &all->sprites.coordinates[1].texture[2], "textures/blacklight.xpm");

	all->sprites.coller = 0;
	all->sprites.coller_max = 89;
	all->sprites.coller_min = 0;
	all->sprites.coller_mod = 45;

	/* */
	all->sprites.coordinates[0].x = 1.5;
	all->sprites.coordinates[0].y = 19.5;
	all->sprites.coordinates[0].u_div = 1;
	all->sprites.coordinates[0].v_div = 1;
	all->sprites.coordinates[0].v_move = 0.0;
	all->sprites.coordinates[0].texture_flag = 0;
	all->sprites.coordinates[0].texture_name = BARREL;
	
	all->sprites.coordinates[1].x = 3.5;
	all->sprites.coordinates[1].y = 22.5;
	all->sprites.coordinates[1].u_div = 1;
	all->sprites.coordinates[1].v_div = 1;
	all->sprites.coordinates[1].v_move = 0.0;
	all->sprites.coordinates[1].texture_flag = 0;
	all->sprites.coordinates[1].texture_name = LIGHT;
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
	sprites_init(all);

	all->player.moveSpeed = 0.3;
	all->player.rotSpeed = 0.3;
	all->animation = 0xDE;
	texture_load(all, &all->wall[0], all->map.no_texture);
	texture_load(all, &all->wall[1], all->map.so_texture);
	texture_load(all, &all->wall[2], all->map.we_texture);
	texture_load(all, &all->wall[3], all->map.ea_texture);
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
	return (0);
}

// int sprite_animation(t_all *all)
// {
// 	all->animation = 0xDE;
// 	// printf("%d\n", i);
// 	draw_sprites(all, all->animation);		
// 	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
// 	all->animation += 1;

int draw_all(t_all *all)
{
	// all->img.img = mlx_new_image(all->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	// all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);

	draw_screen(all);
	draw_border_centre_square(&all->img, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 0xFFFFFF, 0x000000);
	draw_sprites(all);
	draw_minimap(all);

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
	// mlx_hook(all.win, 6, 0, mouse_hook, (void *)&all);

	mlx_loop_hook(all.mlx, draw_all, (void *)&all);

	mlx_loop(all.mlx);
	return (0);
}
