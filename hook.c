#include "cub3d.h"


int *create_dictionary(int **array)
{
	int count_uniq_color;
	int x = -1;
	int y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{

		}
	}
}

int len_int(int *array)
{

}

char *int_to_hex(int number)
{

}

int index_in_array(int *array, int num)
{

}

void create_file(int *dict, int **array)
{
	    FILE *file;

	    file = fopen("fprintf.txt", "w");
		int i = -1;
		while (++i < len_int(dict))
		{
			fprintf(file, "\"%c c #%s\n\"", i, int_to_hex(dict[i])); 
		}
		fprintf(file, "/* pixels */\n");
		int x = -1;
		int y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			x = -1;
			while (++x < SCREEN_WIDTH)
			{
				fprintf(file, "%c", index_in_array(dict, array[x][y]));
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
    {
        int x = 0;
        int y = 0;
        int i = 0;
        int red; int green; int blue; int color;
        // while (i < 4)
        // {
            while (y++ < texHeight)
            {
                x = 0;
                while (x++ < texWidth)
                {
                    color = my_mlx_pixel_get(&all->wall[0], x, y);
                    red = get_r(color) * 0.05 + 0.95 * get_r(9802646);
                    green = get_g(color) * 0.05 + 0.95 * get_g(9802646);
                    blue = get_b(color) * 0.05 + 0.95 * get_b(9802646);
		            color = create_trgb(0, red, green, blue);
                    my_mlx_pixel_set(&all->wall[0], x, y, color);

					                    color = my_mlx_pixel_get(&all->wall[1], x, y);
                    red = get_r(color) * 0.05 + 0.95 * get_r(9802646);
                    green = get_g(color) * 0.05 + 0.95 * get_g(9802646);
                    blue = get_b(color) * 0.05 + 0.95 * get_b(9802646);
		            color = create_trgb(0, red, green, blue);
                    my_mlx_pixel_set(&all->wall[1], x, y, color);

					                    color = my_mlx_pixel_get(&all->wall[2], x, y);
                    red = get_r(color) * 0.05 + 0.95 * get_r(9802646);
                    green = get_g(color) * 0.05 + 0.95 * get_g(9802646);
                    blue = get_b(color) * 0.05 + 0.95 * get_b(9802646);
		            color = create_trgb(0, red, green, blue);
                    my_mlx_pixel_set(&all->wall[2], x, y, color);

					                    color = my_mlx_pixel_get(&all->wall[3], x, y);
                    red = get_r(color) * 0.05 + 0.95 * get_r(9802646);
                    green = get_g(color) * 0.05 + 0.95 * get_g(9802646);
                    blue = get_b(color) * 0.05 + 0.95 * get_b(9802646);
		            color = create_trgb(0, red, green, blue);
                    my_mlx_pixel_set(&all->wall[3], x, y, color);

                }
            }
		// 	i++;
        // }
        red = get_r(all->map.ceilling_color) * 0.25 + 0.75 * get_r(9802646);
		green = get_g(all->map.ceilling_color) * 0.25 + 0.75 * get_g(9802646);
		blue = get_b(all->map.ceilling_color) * 0.25 + 0.75 * get_b(9802646);
		all->map.ceilling_color = create_trgb(0, red, green, blue);
		red = get_r(all->map.floor_color) * 0.25 + 0.75 * get_r(9802646);
		green = get_g(all->map.floor_color) * 0.25 + 0.75 * get_g(9802646);
		blue = get_b(all->map.floor_color) * 0.25 + 0.75 * get_b(9802646);
		all->map.floor_color  = create_trgb(0, red, green, blue);
    }
	if (key == 111)
	{
		int *dict = create_dictionary();
		create_file(dict);
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
