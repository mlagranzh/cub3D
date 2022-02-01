#include "cub3d.h"

void draw_wall(t_all *all, int mapX, int mapY, int side, double perpWallDist, \
								double rayDirX, double rayDirY, double lineHeight, int drawStart, int drawEnd, int x, int num)
{
	t_data texture = all->wall[num];

	//calculate value of wallX
	double wallX; //where exactly the wall was hit
	if (side == 0) 
		wallX = all->player.pos_y + (double)perpWallDist * rayDirY;
	else
		wallX = all->player.pos_x + (double)perpWallDist * rayDirX;
	wallX -= floor((wallX));

	//x coordinate on the texture
	int texX = (int)(wallX * (double)(texWidth));
	if(side == 0 && rayDirX > 0) 
		texX = texWidth - texX - 1;
	if(side == 1 && rayDirY < 0) 
		texX = texWidth - texX - 1;

	// How much to increase the texture coordinate per screen pixel
	double step = texHeight / lineHeight;
	// Starting texture coordinate
	double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
	for(int y = drawStart; y < drawEnd; y++)
	{
		int texY = (int)texPos;
		texPos += step;

		int color = my_mlx_pixel_get(&texture, texX, texY);
		my_mlx_pixel_put(&all->img, x, y, color);
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
			write(1, "Texture not found!\n", 20);
			exit(1);
		}
		all->wall[num].addr = mlx_get_data_addr(all->wall[num].img,  &all->wall[num].bits_per_pixel, \
														&all->wall[num].line_length, &all->wall[num].endian);
	num++;
}