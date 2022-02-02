#include "cub3d.h"

void	draw_map_square(t_data *img, int y, int x, int size, int color)
{
	int i;
	int j;
	int size;

	i = 0;
	size = CEL_SIZE;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
				new_color = 0x000000;
			my_mlx_pixel_put(img, x * CEL_SIZE + i, y * CEL_SIZE + j, new_color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_all *all)
{
	float x;
	float y;
	int	i;

	x = all->player.pos_x;
	y = all->player.pos_y;
	i = 0;
	while (++i < 5)
	{
		if (all->map.map[(int)x][(int)y] == '1')
			break;
		if (i == 1)
			draw_square(&all->img, y, x, 0x000000);
		else
			draw_square(&all->img, y, x, 0xFF00FF);
		x += all->player.dir_x;
		y += all->player.dir_y;
	}
}

void	draw_map(t_all *all) // [width][height]
{
	int map_width = 20;
	int map_height = 20;
	int map_color = 0x858585;
	int i;
	int j;

	// рисует фон карты
	// draw_map_square(&all->img, 0, 0, map_width * CEL_SIZE, map_color);

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
			// if (x >= 0 && y >= 0 && x < all->map.width && y < all->map.height
			// 	&& all->map.map[x][y] == '1')
				// draw_map_square(&all->img, i, j, CEL_SIZE, 0xFFFFFF);
		}
	}
	// Рисует игрока
	// draw_map_square(&all->img, 10, 10, 3, 0xFF00FF);
}
