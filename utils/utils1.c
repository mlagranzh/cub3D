/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:28:52 by celys             #+#    #+#             */
/*   Updated: 2022/01/12 02:37:46 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		my_hook(int key, t_all *all)
{
	if (key == 13) //W
	{
		double moveSpeed = 0.1;
		if(all->map[(int)(all->pos_x + all->dir_x * moveSpeed)][(int)(all->pos_y)] == '0')
			all->pos_x += all->dir_x * moveSpeed;
		if(all->map[(int)(all->pos_x)][(int)(all->pos_y + all->dir_y * moveSpeed)] == '0') 
	  		all->pos_y += all->dir_y * moveSpeed;
	}
	if (key == 1)  //S
	{
		double moveSpeed = 0.1;
		if(all->map[(int)(all->pos_x + all->dir_x * moveSpeed)][(int)(all->pos_y)] == '0')
			all->pos_x -= all->dir_x * moveSpeed;
		if(all->map[(int)(all->pos_x)][(int)(all->pos_y + all->dir_y * moveSpeed)] == '0') 
	  		all->pos_y -= all->dir_y * moveSpeed;
	}
	if (key == 0) //A
	{
	}
	if (key == 2) //D
	{
		double rotSpeed = 0.1;
		double oldDirX = all->dir_x;
		all->dir_x = all->dir_x * cos(rotSpeed) - all->dir_y * sin(rotSpeed);
      	all->dir_y = oldDirX * sin(rotSpeed) + all->dir_y * cos(rotSpeed);
      	double oldPlaneX = all->plane_x;
		all->plane_x = all->plane_x * cos(rotSpeed) - all->plane_y * sin(rotSpeed);
		all->plane_y = oldPlaneX * sin(rotSpeed) + all->plane_y * cos(rotSpeed);

		double moveSpeed = 1;
		if(all->map[(int)(all->pos_x + all->dir_x * moveSpeed)][(int)(all->pos_y)] == '0')
			all->pos_x += all->dir_x * moveSpeed;
		if(all->map[(int)(all->pos_x)][(int)(all->pos_y + all->dir_y * moveSpeed)] == '0') 
	  		all->pos_y += all->dir_y * moveSpeed;

	}
	// if (key == 126) //вверх
	// 	all->dir_y += 0.1;
	// if (key == 125) //вниз
	// 	all->dir_y -= 0.1;
	if (key == 123) //влево
	{
		double rotSpeed = 5;
		double oldDirX = all->dir_x;
		all->dir_x = all->dir_x * cos(-rotSpeed) - all->dir_y * sin(-rotSpeed);
      	all->dir_y = oldDirX * sin(-rotSpeed) + all->dir_y * cos(-rotSpeed);
      	double oldPlaneX = all->plane_x;
		all->plane_x = all->plane_x * cos(-rotSpeed) - all->plane_y * sin(-rotSpeed);
		all->plane_y = oldPlaneX * sin(-rotSpeed) + all->plane_y * cos(-rotSpeed);
	}
	if (key == 124) //вправо
	{
		double rotSpeed = 5;
		double oldDirX = all->dir_x;
		all->dir_x = all->dir_x * cos(rotSpeed) - all->dir_y * sin(rotSpeed);
      	all->dir_y = oldDirX * sin(rotSpeed) + all->dir_y * cos(rotSpeed);
      	double oldPlaneX = all->plane_x;
		all->plane_x = all->plane_x * cos(rotSpeed) - all->plane_y * sin(rotSpeed);
		all->plane_y = oldPlaneX * sin(rotSpeed) + all->plane_y * cos(rotSpeed);
	}

	if (key == 53)
		exit(0);
	all->img.img = mlx_new_image(all->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);
	draw_screen(all);
	draw_map(&all->img, all->map);
	draw_player(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
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