#include "cub3d.h"

void	draw_map_square(t_data *img, int y, int x, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
				my_mlx_pixel_put(img, x * CEL_SIZE + i, y * CEL_SIZE + j, 0x000000);
			else
				my_mlx_pixel_put(img, x * CEL_SIZE + i, y * CEL_SIZE + j, color);
			j++;
		}
		i++;
	}
}

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
	draw_map_square(&all->img, 9, 9, CEL_SIZE, 0xFF0000);
}

void	draw_map(t_all *all) // [width][height]
{
	int map_width = 20;
	int map_height = 20;
	int map_color = 0x858585;
	int i;
	int j;

	// рисует фон карты
	draw_map_square(&all->img, 0, 0, map_width * CEL_SIZE, map_color);

	i = -1;
	int y = all->player.pos_y - map_height / 2 - 1;
	int x;
	while (i < map_height - 1) // Вертикальные полосы
	{
		i++;
		y++;
		j = -1;
		x = all->player.pos_x - map_width / 2 - 1; 
		while (j < map_width - 1) // Горизонтальные полосы
		{
			j++;
			x++;
			if (x >= 0 && y >= 0 && x < all->map.width && y < all->map.height
				&& all->map.map[x][y] == '1')
				draw_map_square(&all->img, i, j, CEL_SIZE, 0xFFFFFF);
		}
	}
	// Рисует игрока
	// draw_map_square(&all->img, 10, 10, 3, 0xFF00FF);
	draw_player(all);
}
