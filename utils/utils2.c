#include "../cub3d.h"

int get_hex(int r, int g, int b)
{
    return (((1 << 24) + (r << 16) + (g << 8) + b));
}