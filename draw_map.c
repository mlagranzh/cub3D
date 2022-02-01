#include "cub3d.h"

void	draw_square(t_data *img, int y, int x, int size, int color)
{
	int i;
	int j;
	int new_color;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			new_color = color;
			if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
				new_color = 0xFFFF00;
			my_mlx_pixel_put(img, x * CEL_SIZE + i, y * CEL_SIZE + j, new_color);
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
				draw_square(img, j, i, CEL_SIZE, 0xFFFFFF);
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

	// draw_square(&all->img, all->player.pos_y, all->player.pos_x, 6, 0xFF00FF);
	x = all->player.pos_x;
	y = all->player.pos_y;
	i = 0;
	while (++i < 5)
	{
		if (all->map.map[(int)x][(int)y] == '1')
			break;
		draw_square(&all->img, y, x, 4, 0xFF00FF);
		x += all->player.dir_x;
		y += all->player.dir_y;
	}
}

