#include "cub3d.h"

static void draw(t_all *all, t_raycast *raycast, int x, int texX)
{
	int y;
	int color;
	double texPos; // Начальная координата текстуры
	double step; // Насколько увеличить координату текстуры на пиксель экрана
	int texY;

	step = texHeight / raycast->line_height;
	texPos = (raycast->draw_start - SCREEN_HEIGHT / 2 + raycast->line_height / 2) * step;
	y = raycast->draw_start;
	while (y < raycast->draw_end)
	{
		texY = (int)texPos;
		texPos += step;
		color = my_mlx_pixel_get(&all->wall[raycast->side * (raycast->step_y + 2) + (!raycast->side) * (raycast->step_x + 1)], texX, texY);
		my_mlx_pixel_put(&all->img, x, y, color);
		y++;
	}
}

void draw_wall(t_all *all, t_raycast *raycast, int x)
{
	int texX; //координата x на текстуре
	double wallX; //где именно в стену попали

	if (raycast->side == 0) 
		wallX = all->player.pos_y + (double)raycast->perp_wall_dist * raycast->ray_dir_y;
	else
		wallX = all->player.pos_x + (double)raycast->perp_wall_dist * raycast->ray_dir_x;
	wallX -= floor((wallX));

	texX = (int)(wallX * (double)(texWidth));
	if(raycast->side == 0 && raycast->ray_dir_x > 0) 
		texX = texWidth - texX - 1;
	if(raycast->side == 1 && raycast->ray_dir_y < 0) 
		texX = texWidth - texX - 1;
	draw(all, raycast, x, texX);
}