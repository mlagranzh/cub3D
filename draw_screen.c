#include "cub3d.h"

typedef struct s_line
{
	int x; // Горизонтальная координата линии
	int y_start; // Начальная вертикальная координата
	int y_end; // Конечная вертикальная координата
	struct s_line *next;
}	t_line;

typedef struct s_picture
{
	int x_start;
	int x_end;
	int map_x; // x координата блока на 2D карте
	int map_y; // y координата блока на 2D карте
	int side; // В какую сторону блока мы ударились
	t_data texture; // Текстура для рисования, из нее берем цвета
	t_line *param; // Ссылка на текщую линию
	t_line *first_param; // Ссылка на первую линию
}	t_picture;

/* Здесь можно тестить, типа песочница
void	test_draw(t_all *all)
{
	int pixel;

	int texture_size_x = 64;
	int texture_size_y = 64;
	int fact_size_x = SCREEN_WIDTH / 2;
	int fact_size_y = SCREEN_HEIGHT / 2;
	
	double coeficient_x = (double)texture_size_x / (double)fact_size_x;

	double sdvig_x = 100;
	double sdvig_y = 100;

	double x = 0;
	double y = 0;
	while (x < fact_size_x)
	{
		y = 0;
		double coeficient_y = (double)texture_size_y / (double)fact_size_y;
		while (y < fact_size_y)
		{
			pixel = my_mlx_pixel_get(&all->wall[0], x * coeficient_x, y * coeficient_y);
			my_mlx_pixel_put(&all->img, x + sdvig_x, y + sdvig_y, pixel);
			y += 1.;
		}
		x += 1.;
	}
}
*/

void	draw_wall_2(t_picture picture, t_data img)
{
	// Размер текстуры (которая лежит в файле)
	int texture_size_x = 64; 
	int texture_size_y = 64;

	// Количество вертикальных линий, которых нужно нарисовать фактически
	int fact_size_x = picture.param->x - picture.first_param->x; 
	
	// Коэфициенты отличия размера текстуры и рисуемой картинки
	double coeficient_x = (double)texture_size_x / (double)fact_size_x;
	double coeficient_y;

	// Счетчики для текстуры (работают вместе с коэфициентом)
	double x = 0;
	double y = 0;

	// Сдивигаем указатель "бегунок" на первую линию
	picture.param = picture.first_param;

	while (1)
	{
		// Количество пикселей в рисуемой линии
		int fact_size_y = picture.param->y_end - picture.param->y_start;
		
		coeficient_y = (double)texture_size_y / (double)fact_size_y;
		y = 0;
		while (picture.param->y_start < picture.param->y_end)
		{
			int pixel = my_mlx_pixel_get(&picture.texture, x * coeficient_x, y * coeficient_y);
			my_mlx_pixel_put(&img, picture.param->x, picture.param->y_start, pixel);
			y++;
			picture.param->y_start++;
		}
		x++;
		if (picture.param->next == NULL)
			break ;
		picture.param = picture.param->next;
	}
}

void	x_calculate_start(t_all *all, t_picture *picture)
{
	int x = picture->x_start - 1;
	while (1)
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
			// Проверить, не попал ли луч в стену
			if (map_x == picture->map_x && map_y == picture->map_y)
				hit = 1;
			else if (map_x < 0 || map_y < 0 || all->map.map[map_x] == NULL
				|| all->map.map[map_x][map_y] == '\0')
			{
				return ;
			}
		}
		picture->x_start = x;
		x--;
	}
}

void	draw_screen(t_all *all)
{
	int x;

	t_picture picture;
	picture.param = NULL;
	
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

		// Условия if
		// Если главный цикл только начат
		// Если мы дошли до края текущего кубика на 2D карте
		// Если кубик тот же, но мы перешли на другую его сторону
		if (picture.param == NULL || (map_x != picture.map_x && map_y != picture.map_y) || side != picture.side)
		{
			if (picture.param != NULL && ((map_x != picture.map_x && map_y != picture.map_y) || side != picture.side))
			{
				// Рисуем одну из сторон кубика
				draw_wall_2(picture, all->img);
				// free picture
			}
			picture.map_x = map_x;
			picture.map_y = map_y;
			picture.side = side;
			picture.param = (t_line *)malloc(sizeof(t_line));
			picture.param->next = NULL;
			picture.first_param = picture.param;
			picture.texture = all->wall[side * (step_y + 2) + (!side) * (step_x + 1)];
		}
		else // Попадаем сюда, если кубик еще не пройден
		{
			picture.param->next = (t_line *)malloc(sizeof(t_line));
			picture.param = picture.param->next;
			picture.param->next = NULL;
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

		// Запоминаем данные, которые собрали по линии
		picture.param->x = x;
		picture.param->y_start = draw_start;
		picture.param->y_end = draw_end;

		draw_wall(all, map_x, map_y, side, perp_wall_dist, ray_dir_x, ray_dir_y, 
					line_height, draw_start, draw_end, x, num);
		x++;
	}
	draw_wall_2(picture, all->img);
}
