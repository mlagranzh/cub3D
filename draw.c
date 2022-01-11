/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:30:59 by celys             #+#    #+#             */
/*   Updated: 2022/01/11 18:37:18 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_screen(t_all *all)
{
	double pos_x = 22, pos_y = 12;//начальная позиция x и y
	double dir_x = -1, dir_y = 0;//начальный вектор направления
	double plane_x = 0, plane_y = 0.66;//2D-лучевая версия плоскости камеры

	double time = 0;//время текущего кадра
	double oldTime = 0;//время предыдущего кадра

	int x = 0;
	while (x < SCREEN_HEIGHT)
	{
		//вычисляем положение и направление луча
		double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;//x-координата в пространстве камеры
		double ray_dir_x = dir_x + plane_x * camera_x;
		double ray_dir_y = dir_y + plane_y * camera_x;
		//в какой ячейке карты мы находимся
		int map_x = (int)pos_x;
		int map_y = (int)pos_y;

		//длина луча от текущей позиции до следующей стороны x или y
		double side_dist_x;
		double side_dist_y;

		//длина луча от одной стороны x или y до следующей стороны x или y
		double delta_dist_x, delta_dist_y;
		delta_dist_x = sqrt(1 + ((ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x)));
		delta_dist_y = sqrt(1 + ((ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y)));
		// 	delta_dist_x = fabs(1 /ray_dir_x); //то же самое
		// delta_dist_y = fabs(1 / ray_dir_y);

		double perp_wall_dist; // переменная для вычисления длинны луча

		//в каком направлении делать шаг в направлении x или y (либо +1, либо -1)
      	int step_x;
      	int step_y;

		int hit = 0;//был ли удар по стене?
      	int side;//был удар по стороне стены x или y?

		// вычисляем шаг и начальный side_dist
		if(ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
		if(ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
		}

		//ДДА - бежим пока не ударимся в стену
		while (hit == 0)
		{
			//перейти к следующему квадрату карты
			//либо в направлении x, либо в направлении y
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			//Проверить, не попал ли луч в стену
			if (all->map[map_x][map_y] != '0')
				hit = 1;
		}

		//Рассчитываем расстояние, проецируемое на направление камеры
		if(side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
      	else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		//Рассчитываем высоту линии для рисования на экране
      	int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

		//вычисляем самый низкий и самый высокий пиксель,
		//чтобы заполнить текущую полосу
		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if(draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if(draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		//выбираем цвет
		int color;
		
		if (all->map[map_x][map_y] == '1')
			color = 0xFF0F0F;
		else if (all->map[map_x][map_y] == '2')
			color = 0xFF0000;
		else if (all->map[map_x][map_y] == '3')
			color = 0x00FF00;
		else if (all->map[map_x][map_y] == '4')
			color = 0x0000FF;
		else
			color = 0xFFFFFF;			
		//придать сторонам x и y разную яркость
  		if(side == 1)
			color = color / 2;

		draw_ver_line(all, x, draw_start, draw_end, color);//
		// printf("x = %i %i < y < %i\n", x, draw_start, draw_end);
		x++;
	}
}