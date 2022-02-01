#include "cub3d.h"

typedef struct s_sprite
{
    double x;
    double y;
    t_data *texture;
}   t_sprite;

#define SPRITES_NUM 5

void initial_sprites(t_all *all)
{
    t_data *data;
    int img_width;
    int img_height;

    data = mlx_xpm_file_to_image(all->mlx, "textures/barrel.xpm", &img_width, &img_height);
    t_sprite sprites[SPRITES_NUM] =
    {
        {1.0, 2.0, data},
        {1.0, 2.0, data},
        {1.0, 2.0, data},
        {1.0, 2.0, data},
        {1.0, 2.0, data}
    };
}