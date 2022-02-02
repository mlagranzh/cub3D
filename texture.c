#include "cub3d.h"

void draw_wall(t_all *all, t_raycast *raycast, int x)
{
	int mapX = raycast->map_x;
	int mapY = raycast->map_y;
	int side = raycast->side;
	double rayDirX = raycast->ray_dir_x;
	double rayDirY = raycast->ray_dir_y;
	int num = side * (raycast->step_y + 2) + (!side) * (raycast->step_x + 1);
	double perpWallDist = raycast->perp_wall_dist;
	int drawStart = raycast->draw_start;
	int drawEnd = raycast->draw_end;
	int lineHeight = raycast->line_height;

	t_data texture;
	int texX; //координата x на текстуре
	int texY;
	double wallX; //где именно в стену попали
	double step; // Насколько увеличить координату текстуры на пиксель экрана
	double texPos; // Начальная координата текстуры


	texture = all->wall[num];
	if (side == 0) 
		wallX = all->player.pos_y + (double)perpWallDist * rayDirY;
	else
		wallX = all->player.pos_x + (double)perpWallDist * rayDirX;
	wallX -= floor((wallX));

	texX = (int)(wallX * (double)(texWidth));
	if(side == 0 && rayDirX > 0) 
		texX = texWidth - texX - 1;
	if(side == 1 && rayDirY < 0) 
		texX = texWidth - texX - 1;
	step = texHeight / lineHeight;
	texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;

	int y;
	int color;

	y = drawStart;
	while (y < drawEnd)
	{
		texY = (int)texPos;
		texPos += step;
		color = my_mlx_pixel_get(&texture, texX, texY);
		my_mlx_pixel_put(&all->img, x, y, color);
		y++;
	}
}

void texture_load(t_all *all, char	*path)
{
	void	*img;
	int		img_width;
	int		img_height;
	static int num = 0;

	all->wall[num].img = mlx_xpm_file_to_image(all->mlx, path, &img_width, &img_height);
	if (all->wall[num].img == NULL)
	{
		write(2, "Texture not found!\n", 20);
		exit(1);
	}
	all->wall[num].addr = mlx_get_data_addr(all->wall[num].img,  &all->wall[num].bits_per_pixel, \
						&all->wall[num].line_length, &all->wall[num].endian);
	num++;
}