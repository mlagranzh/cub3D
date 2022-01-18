#include "cub3d.h"

void	draw_screen(t_all *all)
{
	int x;
	
	x = 0;
	while (x < SCREEN_HEIGHT)
	{
		//вычисляем положение и направление луча
		double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;//x-координата в пространстве камеры
		double ray_dir_x = all->player.dir_x + all->player.plane_x * camera_x;
		double ray_dir_y = all->player.dir_y + all->player.plane_y * camera_x;
		//в какой ячейке карты мы находимся
		int map_x = (int)all->player.pos_x;
		int map_y = (int)all->player.pos_y;

		//длина луча от текущей позиции до следующей стороны x или y
		double side_dist_x;
		double side_dist_y;

		//длина луча от одной стороны x или y до следующей стороны x или y
		double delta_dist_x, delta_dist_y;

		if (ray_dir_x == 0)
 			delta_dist_x = 1e30;
 		else
 			delta_dist_x = fabs(1 / ray_dir_x);
 		if (ray_dir_y == 0)
 			delta_dist_y = 1e30;
 		else
 			delta_dist_y = fabs(1 / ray_dir_y);

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
			side_dist_x = (all->player.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - all->player.pos_x) * delta_dist_x;
		}
		if(ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (all->player.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - all->player.pos_y) * delta_dist_y;
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
			if (all->map.map[map_x][map_y] == '1')
				hit = 1;
		}
		int num = side * (step_y + 2) + (!side) * (step_x + 1);

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
		
		draw_ver_line(all, x, 0, draw_start, all->map.ceilling_color);
		draw_ver_line(all, x, draw_end, SCREEN_HEIGHT, all->map.floor_color);

		draw_wall(all, map_x, map_y, side, perp_wall_dist, ray_dir_x, ray_dir_y, \
					line_height, draw_start, draw_end, x, num);
		x++;
	}
}
