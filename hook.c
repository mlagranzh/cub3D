#include "cub3d.h"

int		my_hook(int key, t_all *all)
{
	if (key == KEY_W || key == KEY_S)
		move_straight(key, all);
	if (key == KEY_A || key == KEY_D)
		move_side(key, all);
	if (key == KEY_LEFT)
		rotate(key, all, ROTATE_SPEED);
	if (key == KEY_RIGHT)
		rotate(key, all, ROTATE_SPEED);
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
		screenshot(all);
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
	if (x != all->player.mouse_x)
	{
		rotSpeed = 0.03;
		if (x > all->player.mouse_x)
			rotSpeed = -rotSpeed;
		rotate(KEY_LEFT, all, rotSpeed);
	}
	all->player.mouse_x = x;
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
