#include "../cub3d.h"

int		my_hook(int key, t_all *all)
{
	if (key == KEY_W)
		move(KEY_W, all);
	if (key == KEY_S)
		move(KEY_S, all);
	if (key == KEY_A)
		move(KEY_A, all);
	if (key == KEY_D)
		move(KEY_D, all);
	if (key == KEY_LEFT)
		rotate(key, all);
	if (key == KEY_RIGHT)
		rotate(key, all);
	if (key == KEY_ESC)
		exit(0);
 	if (key == 13 || key == 1 || key == 0 || key == 2 || key == 123 || key == 124)
	{
		all->img.img = mlx_new_image(all->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
		all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);

		// test_draw(all);

		draw_screen(all);

		draw_map(&all->img, all->map.map);
		draw_player(all);
		
		mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	}
	return (0);
}

int	destroy(t_all *all)
{
	exit (0);
	return (0);
}

void draw_ver_line(t_all *all, int x, int draw_start, int draw_end, int color)
{
	while (draw_start < draw_end)
	{
		my_mlx_pixel_put(&all->img, x, draw_start, color);
		draw_start++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}