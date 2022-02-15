#include "cub3d.h"

void	move_straight(int key, t_all *all)
{
	double move_speed;
	double step_x;
	double step_y;

	move_speed = MOVE_SPEED;
	if (key == KEY_S)
		move_speed = -move_speed;
	step_x = all->player.dir_x * move_speed;
	step_y = all->player.dir_y * move_speed;

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
		if (all->map.map[(int)raise_x][(int)(all->player.pos_y)] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены - дистанция
			raise_x = (double)((int)all->player.pos_x + 1) - distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(raise_x) + 1][(int)(all->player.pos_y)] == '1')
		{
			// Если позиция игрока + шаг > стена - дистанция, то позиция игрока = стена - дистанция
			if (raise_x > (double)((int)raise_x + 1) - distance)
			{
				raise_x = (double)((int)raise_x + 1) - distance;
			}
		}
	}

	// Если смотрим влево (step_x - отрицательный)
	if (all->player.dir_x <= 0)
	{
		// printf("step = %f/%f/%f\n", step_x, all->player.pos_x, all->player.dir_x);
		// Если после шага попадаем в стену
		if (all->map.map[(int)raise_x][(int)(all->player.pos_y)] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены + дистанция
			raise_x = (double)((int)(raise_x + 1)) + distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)raise_x - 1][(int)(all->player.pos_y)] == '1')
		{
			// Если позиция игрока + шаг < стена - дистанция, то позиция игрока = стена + дистанция
			if (raise_x < (double)((int)raise_x) + distance)
				raise_x = (double)((int)raise_x) + distance;
		}
	}

	// Если смотрим вверх (step_y - отрицательный)
	if (all->player.dir_y <= 0)
	{
		// Если после шага попадаем в стену, то приближаемся к стене, но не на весь шаг, а до позиция стены + дистанция
		if (all->map.map[(int)(all->player.pos_x)][(int)raise_y] == '1')
		{
			raise_y = (int)raise_y + 1 + distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x)][(int)raise_y - 1] == '1')
		{
			// Если позиция игрока - шаг < стена + дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_y + step_y < (double)((int)raise_y) + distance)
			{
				raise_y = (double)((int)raise_y) + distance;
			}
		}
	}

	// Если смотрим вниз (step_y - положительный)
	if (all->player.dir_y > 0)
	{
		// Если после шага попадаем в стену, то приближаемся к стене, но не на весь шаг, а до позиция стены - дистанция
		if (all->map.map[(int)(all->player.pos_x)][(int)raise_y] == '1')
			raise_y = (int)raise_y - distance;
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x)][(int)raise_y + 1] == '1')
		{
			// Если позиция игрока + шаг < стена + дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_y + step_y > (double)((int)raise_y) + 1 - distance)
				raise_y = (double)((int)raise_y) + 1 - distance;
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
	double move_speed;
	double step_x;
	double step_y;

	move_speed = MOVE_SPEED;
	if (key == KEY_A)
		move_speed = -move_speed;
	step_x = all->player.dir_y * move_speed;
	step_y = -all->player.dir_x * move_speed;
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
		if (all->map.map[(int)raise_x][(int)all->player.pos_y] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены - дистанция
			raise_x = (double)((int)all->player.pos_x + 1) - distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)raise_x + 1][(int)(all->player.pos_y)] == '1')
		{
			// Если позиция игрока + шаг > стена - дистанция, то позиция игрока = стена - дистанция
			if (all->player.pos_x + step_x > (double)((int)raise_x + 1) - distance)
			{
				raise_x = (double)((int)raise_x + 1) - distance;
			}
		}
	}

	// Если смотрим влево (step_x - отрицательный)
	if (all->player.dir_x <= 0)
	{
		// printf("step = %f/%f/%f\n", step_x, all->player.pos_x, all->player.dir_x);
		// Если после шага попадаем в стену
		if (all->map.map[(int)raise_x][(int)(all->player.pos_y)] == '1')
		{
			// То приближаемся к стене, но не на весь шаг, а до позиция стены + дистанция
			raise_x = (double)((int)(all->player.pos_x + step_x + 1)) + distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)raise_x - 1][(int)(all->player.pos_y)] == '1')
		{
			// Если позиция игрока + шаг < стена - дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_x + step_x < (double)((int)raise_x) + distance)
				raise_x = (double)((int)raise_x) + distance;
		}
	}

	// Если смотрим вверх (step_y - отрицательный)
	if (all->player.dir_y <= 0)
	{
		// Если после шага попадаем в стену, то приближаемся к стене, но не на весь шаг, а до позиция стены + дистанция
		if (all->map.map[(int)(all->player.pos_x)][(int)raise_y] == '1')
		{
			raise_y = (int)raise_y + 1 + distance;
		}
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x)][(int)raise_y - 1] == '1')
		{
			// Если позиция игрока - шаг < стена + дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_y + step_y < (double)((int)raise_y) + distance)
			{
				raise_y = (double)((int)raise_y) + distance;
			}
		}
	}

	// Если смотрим вниз (step_y - положительный)
	if (all->player.dir_y > 0)
	{
		// Если после шага попадаем в стену, то приближаемся к стене, но не на весь шаг, а до позиция стены - дистанция
		if (all->map.map[(int)(all->player.pos_x)][(int)raise_y] == '1')
			raise_y = (int)raise_y - distance;
		// Если после шага попадаем в квадрат перед стеной
		else if (all->map.map[(int)(all->player.pos_x)][(int)raise_y + 1] == '1')
		{
			// Если позиция игрока + шаг < стена + дистанция, то позиция игрока = стена + дистанция
			if (all->player.pos_y + step_y > (double)((int)raise_y) + 1 - distance)
				raise_y = (double)((int)raise_y) + 1 - distance;
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
}

void	rotate(int key, t_all *all, double rotSpeed)
{
	double	old_dir;
	double	old_plane;

	if (key == KEY_RIGHT)
		rotSpeed = -rotSpeed;
	old_dir = all->player.dir_x;
	all->player.dir_x = all->player.dir_x * cos(rotSpeed) - \
						all->player.dir_y * sin(rotSpeed);
	all->player.dir_y = old_dir * sin(rotSpeed) + \
							all->player.dir_y * cos(rotSpeed);
	old_plane = all -> player.plane_x;
	all -> player.plane_x = all -> player.plane_x * cos(rotSpeed) - \
							all -> player.plane_y * sin(rotSpeed);
	all -> player.plane_y = old_plane * sin(rotSpeed) \
							+ all -> player.plane_y * cos(rotSpeed);
}
