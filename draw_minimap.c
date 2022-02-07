#include "cub3d.h"

#define MI_CEL_SIZE			10.
#define MI_SIZE 			20
#define MI_FIELD_COLOR		0x858585
#define MI_WALL_COLOR 		0xFF0000
#define MI_PLAYER_COLOR		0xFFFF00
#define PI 3.141592

static void draw_ray_view(t_all *all, float x, float y)
{
	double angle;
	float x_angle;
	float y_angle;
	int z;

	angle = -0.5;
	while (angle < 0.5)
	{
		x = (MI_SIZE / 2) * MI_CEL_SIZE;
		y = (MI_SIZE / 2) * MI_CEL_SIZE;
		z = 0;
		x_angle = all->player.dir_x * cos(angle) - all->player.dir_y * sin(angle);
		y_angle = all->player.dir_x * sin(angle) + all->player.dir_y * cos(angle);
		while (z++ < 20)
		{
			x += x_angle; 
			y += y_angle;
			if (my_mlx_pixel_get(&all->img, x, y) == MI_WALL_COLOR || \
				my_mlx_pixel_get(&all->img, x, y) == 0 || my_mlx_pixel_get(&all->img, x - 1, y) == 0)
				break;
			my_mlx_pixel_put(&all->img, x, y, MI_PLAYER_COLOR);
		}
		angle += 0.01;
	}
}

void	draw_minimap(t_all *all) // [width][height]
{
	int y;
	int x;

	// Игрок - это всегда центр миникарты. Коэфициент, это сколько нужно вычесть из координаты x и y игрока что бы
	// получить координату левого верхнего квадрата, который входит в границы миникарты
	int coef = MI_SIZE / 2;

	// Рисует фон карты
	draw_border_square(&all->img, 0, 0, MI_SIZE * MI_CEL_SIZE, MI_FIELD_COLOR);

	// Расстояние от позиции игрока до угла квадрата, в котором он находиться
	double buf;
	int mod_x = modf(all->player.pos_x, &buf) * MI_CEL_SIZE;
	int mod_y = modf(all->player.pos_y, &buf) * MI_CEL_SIZE;

	// Рисует квадратик игрока, центр квадратика - точная координата игрока
	draw_border_centre_square(&all->img, (MI_SIZE / 2) * MI_CEL_SIZE, (MI_SIZE / 2) * MI_CEL_SIZE, 1, MI_PLAYER_COLOR, MI_PLAYER_COLOR);

	y = 0;
	while (y < MI_SIZE)
	{
		x = 0;
		while (x < MI_SIZE)
		{
			// Когда x == 0 и y == 0 проверяем квадратик в левом верхнем углу миникарты.
			// К примеру игрок в координате (15;17), вычитаем коэфициент(при текущих размерах он 10) -> (5;7)
			// (5;7) - это квадрат в координатах карты, который нужно нарисовать в (0 - mod_x;0 - mod_y) координатах миникарты.
			int wall_x = (int)all->player.pos_x - coef + x;
			int wall_y = (int)all->player.pos_y - coef + y;

			if (wall_x >= 0 && wall_y >= 0 && wall_x < all->map.width && wall_y < all->map.height
				&& all->map.map[wall_x][wall_y] == '1')
				draw_border_square(&all->img, y * MI_CEL_SIZE - mod_y, x * MI_CEL_SIZE - mod_x, MI_CEL_SIZE, MI_WALL_COLOR);
			x++;
		}
		y++;
	}
	draw_ray_view(all, (MI_SIZE / 2) * MI_CEL_SIZE, (MI_SIZE / 2) * MI_CEL_SIZE);
}
