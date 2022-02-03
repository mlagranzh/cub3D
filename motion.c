#include "cub3d.h"

void move_straight(int key, t_all *all)
{
	double moveSpeed;
	double step_x;
	double step_y;

	moveSpeed = all->player.moveSpeed;
	// if (key == KEY_S)
	// 	moveSpeed = -moveSpeed;
	step_x = all->player.dir_x * moveSpeed;
	step_y = all->player.dir_y * moveSpeed;

	double distance = 0.3;
	
	// Если смотрим вправо
	if (all->player.dir_x > 0)
	{
		// Если после шага попадаем в стену
		if (all->map.map[(int)(all->player.pos_x + step_x)][(int)(all->player.pos_y)] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены - дистанция
			all->player.pos_x = (double)((int)all->player.pos_x + 1) - distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x + step_x) + 1][(int)(all->player.pos_y)] == '1')
		{
			// Если позиция игрока + шаг > стена - дистанция, то позиция игрока = стена - дистанция
			if (all->player.pos_x + step_x > (double)((int)(all->player.pos_x + step_x) + 1) - distance)
				all->player.pos_x = (double)((int)(all->player.pos_x + step_x) + 1) - distance;
			else
				all->player.pos_x += step_x;
		}
		// Иначе
		else
		{
			all->player.pos_x += step_x;
		}
	}

	// Если смотрим влево
	if (all->player.dir_x <= 0)
	{
		// Если после шага попадаем в стену
		if (all->map.map[(int)(all->player.pos_x + step_x)][(int)(all->player.pos_y)] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены + дистанция
			all->player.pos_x = (double)((int)(all->player.pos_x + step_x)) + distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x + step_x) - 1][(int)(all->player.pos_y)] == '1')
		{
			// Если позиция игрока + шаг < стена - дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_x + step_x < (double)((int)(all->player.pos_x + step_x)) + distance)
				all->player.pos_x = (double)((int)(all->player.pos_x + step_x)) + distance;
			else
				all->player.pos_x += step_x;
		}
		// Иначе
		else
		{
			all->player.pos_x += step_x;
		}
	}

	// Если смотрим вверх (step_y - отрицательный)
	if (all->player.dir_y <= 0)
	{
		// Если после шага попадаем в стену
		if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y)] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены + дистанция
			all->player.pos_y = (int)(all->player.pos_y + step_y) + 1 + distance;
			printf("1\n");
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y) - 1] == '1')
		{
			// Если позиция игрока - шаг < стена + дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_y + step_y < (double)((int)(all->player.pos_y + step_y)) + distance)
			{
				all->player.pos_y = (double)((int)(all->player.pos_y + step_y)) + distance;
				printf("2\n");
			}
			else
			{
				all->player.pos_y += step_y;
				printf("3\n");
			}
		}
		else
		{
			all->player.pos_y += step_y;
			printf("4\n");
		}
	}

	// Если смотрим вниз (step_y - положительный)
	if (all->player.dir_y > 0)
	{
		// Если после шага попадаем в стену
		if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y)] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены - дистанция
			all->player.pos_y = (int)(all->player.pos_y + step_y) - distance;
			printf("5\n");
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y) + 1] == '1')
		{
			// Если позиция игрока + шаг < стена + дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_y + step_y > (double)((int)(all->player.pos_y + step_y)) + 1 - distance)
			{
				all->player.pos_y = (double)((int)(all->player.pos_y + step_y)) + 1 - distance;
				printf("6\n");
			}
			else
			{
				all->player.pos_y += step_y;
				printf("7\n");
			}
		}
		else
		{
			all->player.pos_y += step_y;
			printf("8\n");
		}
	}
	
	printf("%f/%f\n", all->player.pos_x, all->player.pos_y);
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
	if (all->map.map[(int)(all->player.pos_x + step_x * DISTANCE)][(int)(all->player.pos_y)] == '0')
		all->player.pos_x += step_x;
	if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y * DISTANCE)] == '0') 
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

