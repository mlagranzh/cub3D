#include "cub3d.h"


void dda_algorithm(t_all *all, t_raycast *raycast)
{
		//ДДА - бежим пока не ударимся в стену
		while (raycast->hit == 0)
		{
			//перейти к следующему квадрату карты
			//либо в направлении x, либо в направлении y
			if (raycast->side_dist_x < raycast->side_dist_y)
			{
				raycast->side_dist_x += raycast->delta_dist_x;
				raycast->map_x += raycast->step_x;
				raycast->side = 0;
			}
			else
			{
				raycast->side_dist_y += raycast->delta_dist_y;
				raycast->map_y += raycast->step_y;
				raycast->side = 1;
			}
			//Проверить, не попал ли луч в стену
			if (all->map.map[raycast->map_x][raycast->map_y] == '1')
				raycast->hit = 1;
		}
		//Рассчитываем расстояние, проецируемое на направление камеры
		if(raycast->side == 0)
			raycast->perp_wall_dist = (raycast->side_dist_x - raycast->delta_dist_x);
      	else
			raycast->perp_wall_dist = (raycast->side_dist_y - raycast->delta_dist_y);
}

static void init(int x, t_all *all, t_raycast *raycast)
{
		raycast->camera_x = 2. * (double)x / (double)SCREEN_WIDTH - 1.;
		raycast->ray_dir_x = all->player.dir_x + all->player.plane_x * raycast->camera_x;
		raycast->ray_dir_y = all->player.dir_y + all->player.plane_y * raycast->camera_x;
		raycast->map_x = (int)all->player.pos_x;
		raycast->map_y = (int)all->player.pos_y;
		if (raycast->ray_dir_x == 0)
 			raycast->delta_dist_x = 1e30;
 		else
 			raycast->delta_dist_x = fabs(1 / raycast->ray_dir_x);
 		if (raycast->ray_dir_y == 0)
 			raycast->delta_dist_y = 1e30;
 		else
 			raycast->delta_dist_y = fabs(1 / raycast->ray_dir_y);
		raycast->hit = 0;
}

// вычисляем шаг и начальный side_dist
static void side_dist(t_all *all, t_raycast *raycast)
{
	if(raycast->ray_dir_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = (all->player.pos_x - raycast->map_x) * raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = (raycast->map_x + 1.0 - all->player.pos_x) * raycast->delta_dist_x;
	}
	if(raycast->ray_dir_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = (all->player.pos_y - raycast->map_y) * raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = (raycast->map_y + 1.0 - all->player.pos_y) * raycast->delta_dist_y;
	}
}

//Рассчитываем высоту линии для рисования на экране
static void where(t_raycast *raycast)
{
    raycast->line_height = (int)(SCREEN_HEIGHT / raycast->perp_wall_dist);

	raycast->draw_start = -raycast->line_height / 2 + SCREEN_HEIGHT / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + SCREEN_HEIGHT / 2;
	if (raycast->draw_end >= SCREEN_HEIGHT)
		raycast->draw_end = SCREEN_HEIGHT - 1;
	// if (raycast->draw_end < 0)
	// 	raycast->draw_end = SCREEN_HEIGHT - 1;
}

void	draw_screen(t_all *all)
{
	int x;
	t_raycast *raycast;

	x = -1;
	raycast = malloc(sizeof(t_raycast));

	while (++x < SCREEN_WIDTH)
	{
		init(x, all, raycast);
		side_dist(all, raycast);
		dda_algorithm(all, raycast);
		where(raycast);
		draw_ver_line(all, x, 0, raycast->draw_start, all->map.ceilling_color);
		draw_ver_line(all, x, raycast->draw_end, SCREEN_HEIGHT, all->map.floor_color);
		draw_wall(all, raycast, x);
		all->sprites.z_buffer[x] = raycast->perp_wall_dist;
	}
}


// void draw_wall(t_all *all, int mapX, int mapY, int side, double perpWallDist, \
// 								double rayDirX, double rayDirY, double lineHeight, int drawStart, int drawEnd, int x, int num)
// {
// 	t_data texture = all->wall[num];

// 	//calculate value of wallX
// 	double wallX; //where exactly the wall was hit
// 	if (side == 0) 
// 		wallX = all->player.pos_y + (double)perpWallDist * rayDirY;
// 	else
// 		wallX = all->player.pos_x + (double)perpWallDist * rayDirX;
// 	wallX -= floor((wallX));

// 	//x coordinate on the texture
// 	int texX = (int)(wallX * (double)(texWidth));
// 	if(side == 0 && rayDirX > 0) 
// 		texX = texWidth - texX - 1;
// 	if(side == 1 && rayDirY < 0) 
// 		texX = texWidth - texX - 1;

// 	// How much to increase the texture coordinate per screen pixel
// 	double step = texHeight / lineHeight;
// 	// Starting texture coordinate
// 	double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
// 	for(int y = drawStart; y < drawEnd; y++)
// 	{
// 		int texY = (int)texPos;
// 		texPos += step;

// 		int color = my_mlx_pixel_get(&texture, texX, texY);
// 		my_mlx_pixel_put(&all->img, x, y, color);
// 	}
// }


// void	draw_screen(t_all *all)
// {
// 	int x;
	
// 	x = 0;
// 	while (x < SCREEN_HEIGHT)
// 	{
// 		// Левая сторона экрана -1, центр 0, а правая сторона 1
// 		double camera_x = 2. * (double)x / (double)SCREEN_WIDTH - 1.;
// 		double ray_dir_x = all->player.dir_x + all->player.plane_x * camera_x;
// 		double ray_dir_y = all->player.dir_y + all->player.plane_y * camera_x;
// 		//в какой ячейке карты мы находимся
// 		int map_x = (int)all->player.pos_x;
// 		int map_y = (int)all->player.pos_y;

// 		//длина луча от текущей позиции до следующей стороны x или y
// 		double side_dist_x;
// 		double side_dist_y;

// 		//длина луча от одной стороны x или y до следующей стороны x или y
// 		double delta_dist_x, delta_dist_y;

// 		if (ray_dir_x == 0)
//  			delta_dist_x = 1e30;
//  		else
//  			delta_dist_x = fabs(1 / ray_dir_x);
//  		if (ray_dir_y == 0)
//  			delta_dist_y = 1e30;
//  		else
//  			delta_dist_y = fabs(1 / ray_dir_y);

// 		double perp_wall_dist; // переменная для вычисления длинны луча

// 		//в каком направлении делать шаг в направлении x или y (либо +1, либо -1)
//       	int step_x;
//       	int step_y;

// 		int hit = 0;//был ли удар по стене?
//       	int side;//был удар по стороне стены x или y?

// 		// вычисляем шаг и начальный side_dist
// 		if(ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (all->player.pos_x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - all->player.pos_x) * delta_dist_x;
// 		}
// 		if(ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (all->player.pos_y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - all->player.pos_y) * delta_dist_y;
// 		}

// 		//ДДА - бежим пока не ударимся в стену
// 		while (hit == 0)
// 		{
// 			//перейти к следующему квадрату карты
// 			//либо в направлении x, либо в направлении y
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			//Проверить, не попал ли луч в стену
// 			if (all->map.map[map_x][map_y] == '1')
// 				hit = 1;
// 		}
		
// 		int num = side * (step_y + 2) + (!side) * (step_x + 1);

// 		//Рассчитываем расстояние, проецируемое на направление камеры
// 		if(side == 0)
// 			perp_wall_dist = (side_dist_x - delta_dist_x);
//       	else
// 			perp_wall_dist = (side_dist_y - delta_dist_y);

// 		//Рассчитываем высоту линии для рисования на экране
//       	int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

// 		//вычисляем самый низкий и самый высокий пиксель,
// 		//чтобы заполнить текущую полосу
// 		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
// 		if(draw_start < 0)
// 			draw_start = 0;
		
// 		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
// 		if(draw_end >= SCREEN_HEIGHT)
// 			draw_end = SCREEN_HEIGHT - 1;
		
// 		// printf("%f\t%f\t\n", side_dist_x, side_dist_y);
// 		draw_ver_line(all, x, 0, draw_start, all->map.ceilling_color);
// 		draw_ver_line(all, x, draw_end, SCREEN_HEIGHT, all->map.floor_color);

// 		draw_wall(all, map_x, map_y, side, perp_wall_dist, ray_dir_x, ray_dir_y, 
// 					line_height, draw_start, draw_end, x, num);
// 		x++;
// 	}
// }
