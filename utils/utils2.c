#include "../cub3d.h"

int get_hex(int r, int g, int b)
{
    return (((1 << 24) + (r << 16) + (g << 8) + b));
}

// Модуль числа
int ft_abs(int num)
{
    if (num < 0)
        num = -num;
    return (num);
}