#include "cub3d.h"

void move(int key, t_all *all)
{
	double moveSpeed;
	double step_x;
	double step_y;

	moveSpeed = all->player.moveSpeed;
	if (key == KEY_S || key == KEY_A)
		moveSpeed = -moveSpeed;
	step_x = all->player.dir_x * moveSpeed;
	step_y = all->player.dir_y * moveSpeed;
	if (key == KEY_A || key == KEY_D)
	{
		step_x = step_y;
		step_y = (step_y / all->player.dir_y) * all->player.dir_x;
	}
	if (all->map.map[(int)(all->player.pos_x + all->player.dir_x * moveSpeed)][(int)(all->player.pos_y)] == '0')
		all->player.pos_x += step_x;
	if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + all->player.dir_y * moveSpeed)] == '0') 
	  	all->player.pos_y += step_y;
}

void rotate(int key, t_all *all)
{
	double oldDir;
	double oldPlane;
	double rotSpeed;
	
	rotSpeed = all->player.rotSpeed;
	if (key == KEY_RIGHT)
		rotSpeed = -rotSpeed;

	oldDir= all->player.dir_x;
	all->player.dir_x = all->player.dir_x * cos(rotSpeed) - all->player.dir_y * sin(rotSpeed);
    all->player.dir_y = oldDir * sin(rotSpeed) + all->player.dir_y * cos(rotSpeed);
    oldPlane = all -> player.plane_x;
	all -> player.plane_x = all -> player.plane_x * cos(rotSpeed) - all -> player.plane_y * sin(rotSpeed);
	all -> player.plane_y = oldPlane * sin(rotSpeed) + all -> player.plane_y * cos(rotSpeed);
}
