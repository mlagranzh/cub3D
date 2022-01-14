#include "../cub3d.h"

time_t programstart;

int		my_hook(int key, t_all *all)
{
	all->player.old_time = all -> player.time;
	all -> player.time += 20; //НАДО ПОПРАВИТЬ
    double frameTime = (all -> player.time - all -> player.old_time) / 1000.0; //frameTime is the time this frame has taken, in seconds
    // printf("%f\n", all -> player.time); //FPS counter
    //speed modifiers
    double moveSpeed = frameTime * 15.0; //the constant value is in squares/second
    double rotSpeed = frameTime * 8.0; //the constant value is in radians/second
	if (key == 13) //W
	{
		if(all->map.map[(int)(all->player.pos_x + all->player.dir_x * moveSpeed)][(int)(all->player.pos_y)] == '0')
			all->player.pos_x += all->player.dir_x * moveSpeed;
		if(all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + all->player.dir_y * moveSpeed)] == '0') 
	  		all->player.pos_y += all->player.dir_y * moveSpeed;
	}
	if (key == 1)  //S
	{
		// double moveSpeed = 0.1;
		if(all->map.map[(int)(all->player.pos_x + all->player.dir_x * moveSpeed)][(int)(all->player.pos_y)] == '0')
			all->player.pos_x -= all->player.dir_x * moveSpeed;
		if(all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + all->player.dir_y * moveSpeed)] == '0') 
	  		all->player.pos_y -= all->player.dir_y * moveSpeed;
	}
	if (key == 0) //A
	{
		if(all->map.map[(int)(all->player.pos_x + all->player.dir_x * moveSpeed)][(int)(all->player.pos_y)] == '0')
			all->player.pos_x -= all->player.dir_y * moveSpeed;
		if(all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + all->player.dir_y * moveSpeed)] == '0') 
	  		all->player.pos_y -= all->player.dir_x * moveSpeed;
		
		// if(all->map.map[(int)(all->player.pos_x + all->player.dir_x * moveSpeed)][(int)(all->player.pos_y)] == '0')
		// 	all->player.pos_x += all->player.dir_x * moveSpeed;
		// if(all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + all->player.dir_y * moveSpeed)] == '0') 
	  	// 	all->player.pos_y += all->player.dir_y * moveSpeed;
	}
	if (key == 2) //D
	{
		// double rotSpeed = 0.1;
		if(all->map.map[(int)(all->player.pos_x + all->player.dir_x * moveSpeed)][(int)(all->player.pos_y)] == '0')
			all->player.pos_x += all->player.dir_y * moveSpeed;
		if(all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + all->player.dir_y * moveSpeed)] == '0') 
	  		all->player.pos_y += all->player.dir_x * moveSpeed;

		// // double moveSpeed = 1;
		// if(all->map.map[(int)(all->player.pos_x + all->player.dir_x * moveSpeed)][(int)(all->player.pos_y)] == '0')
		// 	all->player.pos_x += all->player.dir_x * moveSpeed;
		// if(all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + all->player.dir_y * moveSpeed)] == '0') 
	  	// 	all->player.pos_y += all->player.dir_y * moveSpeed;

	}
	// if (key == 126) //вверх
	// {
	// }
	// if (key == 125) //вниз
	// 	all->player.dir_y -= 0.1;
	if (key == 123) //влево
	{
		// double rotSpeed = 5;
		double oldDirX = all->player.dir_x;
		all->player.dir_x = all->player.dir_x * cos(rotSpeed) - all->player.dir_y * sin(rotSpeed);
      	all->player.dir_y = oldDirX * sin(rotSpeed) + all->player.dir_y * cos(rotSpeed);
      	double oldPlaneX = all -> player.plane_x;
		all -> player.plane_x = all -> player.plane_x * cos(rotSpeed) - all -> player.plane_y * sin(rotSpeed);
		all -> player.plane_y = oldPlaneX * sin(rotSpeed) + all -> player.plane_y * cos(rotSpeed);

	}
	if (key == 124) //вправо
	{
		// double rotSpeed = 5;
		double oldDirX = all->player.dir_x;
		all->player.dir_x = all->player.dir_x * cos(-rotSpeed) - all->player.dir_y * sin(-rotSpeed);
      	all->player.dir_y = oldDirX * sin(-rotSpeed) + all->player.dir_y * cos(-rotSpeed);
      	double oldPlaneX = all -> player.plane_x;
		all -> player.plane_x = all -> player.plane_x * cos(-rotSpeed) - all -> player.plane_y * sin(-rotSpeed);
		all -> player.plane_y = oldPlaneX * sin(-rotSpeed) + all -> player.plane_y * cos(-rotSpeed);
	}

	if (key == 53)
		exit(0);
 
	//	for(int y = 0; y < h; y++) for(int x = 0; x < w; x++) buffer[y][x] = 0; 
	//  может лучше использовать это? 
	all->img.img = mlx_new_image(all->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);
	draw_screen(all);
	
	draw_map(&all->img, all->map.map);
	draw_player(all);
	
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	all -> player.old_time = time(NULL);
	return (0);
}

int	destroy(t_all *all)
{
	exit (0);
	return (0);
}

void draw_ver_line(t_all *all, int x, int draw_start, int draw_end, int color)
{
	while (draw_start < draw_end)
	{
		my_mlx_pixel_put(&all->img, x, draw_start, color);
		draw_start++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}