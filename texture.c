#include "cub3d.h"

#define texWidth 64
#define texHeight 64

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


void draw_wall(t_all *all, int mapX, int mapY, int side, int perpWallDist, \
                double rayDirX, double rayDirY, int lineHeight, int drawStart, int drawEnd, int x, \
                char	*texture)
{
    //texturing calculations
      int texNum = all->map.map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

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

        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
       
        int t =  *(unsigned int*)(texture + texY*texHeight + texX);
        int r =  *(unsigned int*)(texture + texY*texHeight + texX + 1);
        int g =  *(unsigned int*)(texture + texY*texHeight + texX + 2);
        int b =  *(unsigned int*)(texture + texY*texHeight + texX + 3);

        int color = create_trgb(t, r, g, b);
        if (side == 1)
            color = (color >> 1) & 8355711;
        
        int pixel = y * all->img.line_length + x * (all->img.bits_per_pixel / 8);
        all->img.addr[pixel] = (color) & 0xFF;
        all->img.addr[pixel + 1] = (color >> 8) & 0xFF;
        all->img.addr[pixel + 2] = (color >> 16) & 0xFF;
        all->img.addr[pixel + 3] = (color >> 24);
        // my_mlx_pixel_put(&all->img, x, y, color);
    }
}

char	*texture_load(t_all *all)
{
	void	*img;
	char	*relative_path = "./textures/redbrick.xpm";
	int		img_width;
	int		img_height;
  t_wall  wall;

	img = mlx_xpm_file_to_image(all->mlx, relative_path, &img_width, &img_height);
	char   *addr = mlx_get_data_addr(img,  &wall.bits_per_pixel, &wall.line_length, &wall.endian);
    all -> wall = wall;
    return (addr);
}