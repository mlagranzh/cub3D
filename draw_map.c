#include "cub3d.h"

void	draw_square(t_data *img, int y, int x, int color)
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
				my_mlx_pixel_put(img, x * CEL_SIZE + i, y * CEL_SIZE + j, 0xFFFF00);
			else
				my_mlx_pixel_put(img, x * CEL_SIZE + i, y * CEL_SIZE + j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *img, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(img, j, i, 0xFFFFFF);
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

