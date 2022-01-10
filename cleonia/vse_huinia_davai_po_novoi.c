# include "../mlx/mlx.h"
# include "../LIBFT/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int world_map[MAP_WIDTH][MAP_HEIGHT]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	t_data		img;
	char		**map;
}	t_all;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_ver_line(t_all *all, int x, int draw_start, int draw_end, int color);
int		destroy(t_all *all);

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
			if (world_map[map_x][map_y] > 0)
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
		switch (world_map[map_x][map_y])
		{
		case 1:
			color = 0xFF0F0F;
			break;
		case 2:
			color = 0xFF0000;
			break;
		case 3:
			color = 0x00FF00;
			break;
		case 4:
			color = 0x0000FF;
			break;
		default:
			color = 0xFFFFFF;
			break;
		}
			
		//придать сторонам x и y разную яркость
  		if(side == 1)
			color = color / 2;

		draw_ver_line(all, x, draw_start, draw_end, color);//
		// printf("x = %i %i < y < %i\n", x, draw_start, draw_end);
		x++;
	}
}

int		my_hook(int key, t_all *all)
{
	mlx_clear_window(all->mlx, all->win);
	// if (key == 13)
	// 	all->player.y -= 4;
	// if (key == 1)
	// 	all->player.y += 4;
	// if (key == 0)
	// 	all->player.x -= 4;
	// if (key == 2)
	// 	all->player.x += 4;
	if (key == 53)
		exit(0);
	all->img.img = mlx_new_image(all->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);
	draw_screen(all);
	// draw_ver_line(all, 100, 0, 100, 0xFFFFFF);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (0);
}

int main()
{
	t_all	all;

	all.mlx = mlx_init();
	// all.map = make_map("map.cub");
	all.win = mlx_new_window(all.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub");
	all.img.img = mlx_new_image(all.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);

	mlx_hook(all.win, 2, 1L << 2, my_hook, (void *)&all);
	mlx_hook(all.win, 17, 0L, destroy, (void *)&all);

	mlx_loop(all.mlx);
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

int	destroy(t_all *all)
{
	exit (0);
	return (0);
}