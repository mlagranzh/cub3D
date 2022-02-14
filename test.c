#include "cub3d.h"

int main()
{
    int a = 2147483647;
    int i = 0;
    int max;
    int min;

    max = 1;
    min = 0;
    while (i++ < 100)
    {
        printf("%i %i\n", a + max, max);
        max *= 10;
    }
}

// -2137493649
// -2047583649