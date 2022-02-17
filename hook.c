/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:20:49 by celys             #+#    #+#             */
/*   Updated: 2022/02/17 03:06:46 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy(t_all *all)
{
	cub_destroy(all);
	exit(0);
	return (0);
}

void	light_on_off(t_all *all)
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

int	key_release(int key, t_all *all)
{
	if (key == KEY_FN_F12)
	{
		draw_screen(all);
		draw_sprites(all);
		draw_minimap(all);
		mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	}	
	return (SUCCESS);
}

int	key_press(int key, t_all *all)
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
		destroy(all);
	if (key == KEY_SPACE)
		light_on_off(all);
	if (key == KEY_ENTER)
		fog(all);
	if (key == KEY_FN_F12)
		screenshot(all);
	if (key != KEY_FN_F12)
	{
		draw_screen(all);
		draw_sprites(all);
		draw_minimap(all);
		mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	}
	return (SUCCESS);
}

int	mouse_hook(int x, int y, t_all *all)
{
	double	rot_speed;

	(void) y;
	mlx_mouse_hide();
	if (x < 0 || x > SCREEN_WIDTH)
		mlx_mouse_move(all->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	if (x != all->player.mouse_x)
	{
		rot_speed = 0.03;
		if (x > all->player.mouse_x)
			rot_speed = -rot_speed;
		rotate(KEY_LEFT, all, rot_speed);
	}
	all->player.mouse_x = x;
	draw_screen(all);
	draw_sprites(all);
	draw_minimap(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (0);
}

int	loop_hook(t_all *all)
{
	draw_sprites(all);
	// draw_minimap(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (0);
}
