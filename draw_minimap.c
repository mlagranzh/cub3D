#include "cub3d.h"

#define MI_CEL_SIZE			8.
#define MI_SIZE 			20
#define MI_FIELD_COLOR		0x858585
#define MI_WALL_COLOR 		0xFF0000
#define MI_PLAYER_COLOR		0xFFFF00

void	draw_player_ray(t_all *all, int x, int y)
{
	int i;
	int j;

	i = y - 1;
	while (i < y + 1)
	{
		j = x - 1;
		while (j < x + 1)
		{
			my_mlx_pixel_put(&all->img, j, i, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	draw_player(t_all *all)
{
	// На экране
	float x;
	float y;
	// На карте
	float map_x;
	float map_y;
	int	i;
	int j;

	x = 10 * CEL_SIZE - CEL_SIZE / 2;
	y = 10 * CEL_SIZE - CEL_SIZE / 2;

	map_x = all->player.pos_x;
	map_y = all->player.pos_y;

	while (map_x < 20 && map_y < 20 && map_x > 0 && map_y > 0)
	{
		if (all->map.map[(int)map_x][(int)map_y] == '1')
			break;
		map_x += all->player.dir_x;
		map_y += all->player.dir_y;
		if (x > 0 && y > 0)
			// draw_player_ray(all, x, y);
		x += all->player.dir_x;
		y += all->player.dir_y;
	}
	// Начальная точка игрока
	draw_border_square(&all->img, 9, 9, CEL_SIZE, 0xFF0000);
}

// draw_border_centre_square(&all->img, 10 * MI_CEL_SIZE, 10 * MI_CEL_SIZE, 9 * MI_CEL_SIZE, 0x000000);

void	draw_minimap(t_all *all) // [width][height]
{
	int y;
	int x;

	int coef = MI_SIZE / 2;

	// рисует фон карты
	draw_border_square(&all->img, 0, 0, MI_SIZE * MI_CEL_SIZE, MI_FIELD_COLOR);

	double buf;
	int mod_x = modf(all->player.pos_x, &buf) * MI_CEL_SIZE;
	int mod_y = modf(all->player.pos_y, &buf) * MI_CEL_SIZE;
	// printf("mod %i/%i\n", mod_x, mod_y);

	draw_border_centre_square(&all->img, 10 * MI_CEL_SIZE, 10 * MI_CEL_SIZE, 1, MI_PLAYER_COLOR, MI_PLAYER_COLOR);

	y = 0;
	while (y < MI_SIZE)
	{
		x = 0;
		while (x < MI_SIZE)
		{
			int wall_x = (int)all->player.pos_x - coef + x;
			int wall_y = (int)all->player.pos_y - coef + y;
			if (wall_x >= 0 && wall_y >= 0 && wall_x < all->map.width && wall_y < all->map.height
				&& all->map.map[wall_x][wall_y] == '1')
				draw_border_square(&all->img, y * MI_CEL_SIZE - mod_y, x * MI_CEL_SIZE - mod_x, MI_CEL_SIZE, MI_WALL_COLOR);
			x++;
		}
		y++;
	}
	// Рисует игрока
	// draw_player(all);
}
