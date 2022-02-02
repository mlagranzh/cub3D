#include "cub3d.h"

void move_straight(int key, t_all *all)
{
	double moveSpeed;
	double step_x;
	double step_y;

	moveSpeed = all->player.moveSpeed;
	if (key == KEY_S)
		moveSpeed = -moveSpeed;
	moveSpeed = moveSpeed * 2;
	if (all->player.dir_x < 0)
		step_x = -moveSpeed;
	else
		step_x = moveSpeed;
	if (all->player.dir_y < 0)
		step_y = -moveSpeed;
	else
		step_y = moveSpeed;
	if (all->map.map[(int)(all->player.pos_x + step_x)][(int)(all->player.pos_y)] == '0')
		all->player.pos_x += step_x;
	if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y)] == '0') 
	  	all->player.pos_y += step_y;
	printf("%i/%i\n", (int)(all->player.pos_x + step_x), (int)(all->player.pos_y + step_y));
	printf("%f/%f\n", all->player.pos_x + step_x, all->player.pos_y + step_y);
}

void move_side(int key, t_all *all)
{
	double moveSpeed;
	double step_x;
	double step_y;

	moveSpeed = all->player.moveSpeed;
	if (key == KEY_A)
		moveSpeed = -moveSpeed;
	step_x = all->player.dir_y * moveSpeed;
	step_y = -all->player.dir_x * moveSpeed;
	if (all->map.map[(int)((all->player.pos_x + step_x * DISTANCE))][(int)((all->player.pos_y))] == '0')
		all->player.pos_x += step_x;
	if (all->map.map[(int)((all->player.pos_x))][(int)((all->player.pos_y + step_y * DISTANCE))] == '0') 
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
	// printf("%f\t%f\t%f\t%f\t\n", all->player.dir_x, all->player.dir_y, all -> player.plane_x, all -> player.plane_y);
}

