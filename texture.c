#include "cub3d.h"

#define texWidth 64
#define texHeight 64



void draw_wall(t_all *all, int mapX, int mapY, int side, int perpWallDist, \
                double rayDirX, double rayDirY, int lineHeight, int drawStart, int drawEnd, int x, \
                char	*texture)
{
    //texturing calculations
      int texNum = all->map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) 
        wallX = all->player.pos_y + perpWallDist * rayDirY;
      else
        wallX = all->player.pos_x + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(texWidth));
      if(side == 0 && rayDirX > 0) 
        texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) 
        texX = texWidth - texX - 1;


     // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y < drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;

        int color = *(unsigned int*)(texture + texY*texHeight + texX);
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1)
             color = (color >> 1) & 8355711;
        my_mlx_pixel_put(&all->img, x, y, color);
      }
    }

char	*texture_load(t_all *all)
{
	void	*img;
	char	*relative_path = "./textures/mossy.xpm";
	int		img_width;
	int		img_height;
    t_wall  wall;

	img = mlx_xpm_file_to_image(all->mlx, relative_path, &img_width, &img_height);
	char	*addr = mlx_get_data_addr(img,  &wall.bits_per_pixel, &wall.line_length, &wall.endian);
    
    // for(int x = 0; x < texWidth; x++)
    // for(int y = 0; y < texHeight; y++)
    // {
    //     int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
    //     //int xcolor = x * 256 / texWidth;
    //     int ycolor = y * 256 / texHeight;
    //     int xycolor = y * 128 / texHeight + x * 128 / texWidth;
    //     *(unsigned int*)(addr + texWidth * y + x) = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
    // }

    all->wall = wall;
    return (addr);
}