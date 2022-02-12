#include "cub3d.h"

void move_straight(int key, t_all *all)
{
	double moveSpeed;
	double step_x;
	double step_y;

	moveSpeed = MOVE_SPEED;
	if (key == KEY_S)
		moveSpeed = -moveSpeed;
	step_x = all->player.dir_x * moveSpeed;
	step_y = all->player.dir_y * moveSpeed;
	// printf("mS = %f, s_x = %f\n", moveSpeed, step_x);
	if (key == KEY_S)
	{
		all->player.dir_x *= -1;
		all->player.dir_y *= -1;
	}

	double distance = 0.3;

	double raise_x = step_x + all->player.pos_x;
	double raise_y = step_y + all->player.pos_y;
	
	// Если смотрим вправо (step_x - положительный)
	if (all->player.dir_x > 0)
	{
		// Если после шага попадаем в стену
		if (all->map.map[(int)(all->player.pos_x + step_x)][(int)(all->player.pos_y)] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены - дистанция
			raise_x = (double)((int)all->player.pos_x + 1) - distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x + step_x) + 1][(int)(all->player.pos_y)] == '1')
		{
			// Если позиция игрока + шаг > стена - дистанция, то позиция игрока = стена - дистанция
			if (all->player.pos_x + step_x > (double)((int)(all->player.pos_x + step_x) + 1) - distance)
			{
				raise_x = (double)((int)(all->player.pos_x + step_x) + 1) - distance;
			}
		}
	}

	// Если смотрим влево (step_x - отрицательный)
	if (all->player.dir_x <= 0)
	{
		// printf("step = %f/%f/%f\n", step_x, all->player.pos_x, all->player.dir_x);
		// Если после шага попадаем в стену
		if (all->map.map[(int)(all->player.pos_x + step_x)][(int)(all->player.pos_y)] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены + дистанция
			raise_x = (double)((int)(all->player.pos_x + step_x + 1)) + distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x + step_x) - 1][(int)(all->player.pos_y)] == '1')
		{
			// Если позиция игрока + шаг < стена - дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_x + step_x < (double)((int)(all->player.pos_x + step_x)) + distance)
				raise_x = (double)((int)(all->player.pos_x + step_x)) + distance;
		}
	}

	// Если смотрим вверх (step_y - отрицательный)
	if (all->player.dir_y <= 0)
	{
		// Если после шага попадаем в стену, то приближаемся к стене, но не на весь шаг, а до позиция стены + дистанция
		if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y)] == '1')
		{
			raise_y = (int)(all->player.pos_y + step_y) + 1 + distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y) - 1] == '1')
		{
			// Если позиция игрока - шаг < стена + дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_y + step_y < (double)((int)(all->player.pos_y + step_y)) + distance)
			{
				raise_y = (double)((int)(all->player.pos_y + step_y)) + distance;
			}
		}
	}

	// Если смотрим вниз (step_y - положительный)
	if (all->player.dir_y > 0)
	{
		// Если после шага попадаем в стену, то приближаемся к стене, но не на весь шаг, а до позиция стены - дистанция
		if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y)] == '1')
			raise_y = (int)(all->player.pos_y + step_y) - distance;
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y) + 1] == '1')
		{
			// Если позиция игрока + шаг < стена + дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_y + step_y > (double)((int)(all->player.pos_y + step_y)) + 1 - distance)
				raise_y = (double)((int)(all->player.pos_y + step_y)) + 1 - distance;
		}
	}

	// printf("x = %f / y = %f\n", all->player.pos_x - raise_x, all->player.pos_y - raise_y);

	all->player.pos_x = raise_x;
	all->player.pos_y = raise_y;

	if (key == KEY_S)
	{
		all->player.dir_x *= -1;
		all->player.dir_y *= -1;
	}
}

void move_side(int key, t_all *all)
{
	double moveSpeed;
	double step_x;
	double step_y;

	moveSpeed = MOVE_SPEED;
	if (key == KEY_A)
		moveSpeed = -moveSpeed;
	step_x = all->player.dir_y * moveSpeed;
	step_y = -all->player.dir_x * moveSpeed;
	if (key == KEY_A)
	{
		all->player.dir_x *= -1;
		all->player.dir_y *= -1;
	}
	double tmp;

	tmp = all->player.dir_x;
	all->player.dir_x = all->player.dir_y;
	all->player.dir_y = tmp;
	all->player.dir_y *= -1;

	double distance = 0.3;

	double raise_x = step_x + all->player.pos_x;
	double raise_y = step_y + all->player.pos_y;
	
	// Если смотрим вправо (step_x - положительный)
	if (all->player.dir_x > 0)
	{
		// Если после шага попадаем в стену
		if (all->map.map[(int)(all->player.pos_x + step_x)][(int)(all->player.pos_y)] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены - дистанция
			raise_x = (double)((int)all->player.pos_x + 1) - distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x + step_x) + 1][(int)(all->player.pos_y)] == '1')
		{
			// Если позиция игрока + шаг > стена - дистанция, то позиция игрока = стена - дистанция
			if (all->player.pos_x + step_x > (double)((int)(all->player.pos_x + step_x) + 1) - distance)
			{
				raise_x = (double)((int)(all->player.pos_x + step_x) + 1) - distance;
			}
		}
	}

	// Если смотрим влево (step_x - отрицательный)
	if (all->player.dir_x <= 0)
	{
		// printf("step = %f/%f/%f\n", step_x, all->player.pos_x, all->player.dir_x);
		// Если после шага попадаем в стену
		if (all->map.map[(int)(all->player.pos_x + step_x)][(int)(all->player.pos_y)] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены + дистанция
			raise_x = (double)((int)(all->player.pos_x + step_x + 1)) + distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x + step_x) - 1][(int)(all->player.pos_y)] == '1')
		{
			// Если позиция игрока + шаг < стена - дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_x + step_x < (double)((int)(all->player.pos_x + step_x)) + distance)
				raise_x = (double)((int)(all->player.pos_x + step_x)) + distance;
		}
	}

	// Если смотрим вверх (step_y - отрицательный)
	if (all->player.dir_y <= 0)
	{
		// Если после шага попадаем в стену, то приближаемся к стене, но не на весь шаг, а до позиция стены + дистанция
		if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y)] == '1')
		{
			raise_y = (int)(all->player.pos_y + step_y) + 1 + distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y) - 1] == '1')
		{
			// Если позиция игрока - шаг < стена + дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_y + step_y < (double)((int)(all->player.pos_y + step_y)) + distance)
			{
				raise_y = (double)((int)(all->player.pos_y + step_y)) + distance;
			}
		}
	}

	// Если смотрим вниз (step_y - положительный)
	if (all->player.dir_y > 0)
	{
		// Если после шага попадаем в стену, то приближаемся к стене, но не на весь шаг, а до позиция стены - дистанция
		if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y)] == '1')
			raise_y = (int)(all->player.pos_y + step_y) - distance;
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y) + 1] == '1')
		{
			// Если позиция игрока + шаг < стена + дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_y + step_y > (double)((int)(all->player.pos_y + step_y)) + 1 - distance)
				raise_y = (double)((int)(all->player.pos_y + step_y)) + 1 - distance;
		}
	}
	// printf("x = %f / y = %f\n", all->player.dir_x, all->player.dir_y);

	all->player.pos_x = raise_x;
	all->player.pos_y = raise_y;

	// all->player.dir_y *= -1;
	if (key == KEY_A)
	{
		all->player.dir_x *= -1;
		all->player.dir_y *= -1;
	}
	all->player.dir_y *= -1;
	tmp = all->player.dir_x;
	all->player.dir_x = all->player.dir_y;
	all->player.dir_y  = tmp;

	
	// printf("%f/%f\n", all->player.pos_x, all->player.pos_y);
}

// void move_side(int key, t_all *all)
// {
// 	double moveSpeed;
// 	double step_x;
// 	double step_y;

// 	moveSpeed = all->player.moveSpeed;
// 	if (key == KEY_A)
// 		moveSpeed = -moveSpeed;
// 	step_x = all->player.dir_y * moveSpeed;
// 	step_y = -all->player.dir_x * moveSpeed;
// 	// printf("mS = %f, s_x = %f\n", moveSpeed, step_x);
// 	if (all->map.map[(int)(all->player.pos_x + step_x * DISTANCE)][(int)(all->player.pos_y)] == '0')
// 		all->player.pos_x += step_x;
// 	if (all->map.map[(int)(all->player.pos_x)][(int)(all->player.pos_y + step_y * DISTANCE)] == '0') 
// 	  	all->player.pos_y += step_y;
// }

void rotate(int key, t_all *all, double rotSpeed)
{
	double oldDir;
	double oldPlane;
	
	if (key == KEY_RIGHT)
		rotSpeed = -rotSpeed;

	oldDir = all->player.dir_x;
	all->player.dir_x = all->player.dir_x * cos(rotSpeed) - all->player.dir_y * sin(rotSpeed);
    all->player.dir_y = oldDir * sin(rotSpeed) + all->player.dir_y * cos(rotSpeed);
    oldPlane = all -> player.plane_x;
	all -> player.plane_x = all -> player.plane_x * cos(rotSpeed) - all -> player.plane_y * sin(rotSpeed);
	all -> player.plane_y = oldPlane * sin(rotSpeed) + all -> player.plane_y * cos(rotSpeed);
}

