#include "../cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	my_mlx_pixel_get(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_square(t_data *img, int y, int x, int color)
{
	int i;
	int j;

	i = 0;
	while (i < CEL_SIZE)
	{
		j = 0;
		while (j < CEL_SIZE)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_border_square(t_data *img, int y, int x, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (x + i < 0 || y + j < 0 || x + i > SCREEN_WIDTH || y + j > SCREEN_HEIGHT)
				continue ;
			if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
				my_mlx_pixel_put(img, x + i, y + j, 0x000000);
			else
				my_mlx_pixel_put(img, x + i, y + j, color);
		}
		i++;
	}
}

// рисует квадрат с черной границей, координаты заданны по середине
void	draw_border_centre_square(t_data *img, int centre_x, int centre_y, int half_size, int inside_color, int border_color)
{
	int i;
	int j;

	i = centre_x - half_size;
	while (i <= centre_x + half_size)
	{
		j = centre_y - half_size - 1;
		while (++j <= centre_y + half_size)
		{
			if (i < 0 || j < 0)
				continue ;
			if (i == centre_x - half_size || j == centre_y - half_size || i == centre_x + half_size || j == centre_y + half_size)
				my_mlx_pixel_put(img, i, j, border_color);
			else
				my_mlx_pixel_put(img, i, j, inside_color);
			// printf("%d\t%d\t\n", i, j);
		}
		i++;
	}
}

unsigned char	get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}
