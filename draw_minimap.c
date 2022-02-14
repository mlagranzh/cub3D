#include "cub3d.h"

#define MI_CEL_SIZE 10.
#define MI_SIZE 20
#define MI_FIELD_COLOR		0x858585
#define MI_WALL_COLOR 		0xFF0000
#define MI_PLAYER_COLOR		0xFFFF00
#define RAY_COLOR  0xc8c8c8

static void	draw_ray_view(t_all *all, float x, float y)
{
	double	angle;
	int		z;

	angle = -0.5;
	while (angle < 0.5)
	{
		x = (MI_SIZE / 2) * MI_CEL_SIZE;
		y = (MI_SIZE / 2) * MI_CEL_SIZE;
		z = 0;
		while (z++ < 20)
		{
			x += all->player.dir_x * cos(angle) - \
							all->player.dir_y * sin(angle);
			y += all->player.dir_x * sin(angle) + \
							all->player.dir_y * cos(angle);
			if (my_mlx_pixel_get(&all->img, x, y) == MI_WALL_COLOR || \
				my_mlx_pixel_get(&all->img, x, y) == 0 || \
				my_mlx_pixel_get(&all->img, x - 1, y) == 0)
				break ;
			my_mlx_pixel_put(&all->img, x, y, RAY_COLOR);
		}
		angle += 0.01;
	}
}

void	draw_minimap(t_all *all)
{
	int	x;
	int	y;
	int	coef;
	double	buf;

	coef = MI_SIZE / 2;
	draw_border_square(&all->img, 0, 0, MI_SIZE * MI_CEL_SIZE, MI_FIELD_COLOR);
	int mod_x = modf(all->player.pos_x, &buf) * MI_CEL_SIZE;
	int mod_y = modf(all->player.pos_y, &buf) * MI_CEL_SIZE;
	draw_border_centre_square(&all->img, (MI_SIZE / 2) * MI_CEL_SIZE, (MI_SIZE / 2) * MI_CEL_SIZE, 1, MI_PLAYER_COLOR, MI_PLAYER_COLOR);

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
	draw_ray_view(all, (MI_SIZE / 2) * MI_CEL_SIZE, (MI_SIZE / 2) * MI_CEL_SIZE);
}