#include "cub3d.h"

typedef struct s_sprite
{
    double x;
    double y;
    t_data *texture;
}   t_sprite;

#define SPRITES_NUM 5

void draw_sprites(t_all *all)
{
    t_data data;

    data.img = mlx_xpm_file_to_image(all->mlx, "textures/barrel.xpm", &data.line_length, &data.line_length);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    t_sprite sprites[SPRITES_NUM] =
    {
        {1.5, 20.5, &data},
        {2.0, 4.0, &data},
        {3.0, 3.0, &data},
        {4.0, 2.0, &data},
        {5.0, 1.0, &data}
    };

    int i = 0;

    while (i < SPRITES_NUM)
    {
        double sprite_x = sprites[i].x - all->player.pos_x;
        double sprite_y = sprites[i].y - all->player.pos_y;

        double inv_det = 1.0 / (all->player.plane_x * all->player.dir_y
            - all->player.dir_x * all->player.plane_y);
        
        double transform_x = inv_det * (all->player.dir_y * sprite_x - all->player.dir_x * sprite_y);
        double transform_y = inv_det * (-all->player.plane_y * sprite_x + all->player.plane_x * sprite_y);

        int sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + transform_x / transform_y));

        #define U_DIV 1
        #define V_DIV 1
        #define V_MOVE 0.0

        int v_move_screen = (int)(V_MOVE / transform_y);

        int sprite_height = abs((int)(SCREEN_HEIGHT / transform_y)) / V_DIV;

        int draw_start_y = -sprite_height / 2 + SCREEN_HEIGHT / 2 + v_move_screen;
        if (draw_start_y < 0)
            draw_start_y = 0;
        int draw_end_y = sprite_height / 2 + SCREEN_HEIGHT / 2 + v_move_screen;
        if (draw_end_y >= SCREEN_HEIGHT)
            draw_end_y = SCREEN_HEIGHT - 1;

        int sprite_width = abs((int)(SCREEN_HEIGHT / transform_y)) / U_DIV;

        int draw_start_x = -sprite_width / 2 + sprite_screen_x;
        if (draw_start_x < 0)
            draw_start_x = 0;
        int draw_end_x = sprite_width / 2 + sprite_screen_x;
        if (draw_end_x > SCREEN_WIDTH)
            draw_end_x = SCREEN_WIDTH;
        
        int stripe = draw_start_x;
        while (stripe < draw_end_x)
        {
            int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x))
                * texWidth / sprite_width) / 256;

            if (transform_y > 0 && transform_y < all->z_buffer[stripe])
            {
                int y = draw_start_y;
                while (y < draw_end_y)
                {
                    int d = (y - v_move_screen) * 256 - SCREEN_HEIGHT * 128 + sprite_height * 128;
                    int tex_y = ((d * texHeight) / sprite_height) / 256;
                    int color = my_mlx_pixel_get(sprites[i].texture, tex_x, tex_y);
                    if (color != 0x000000)
                        my_mlx_pixel_put(&all->img, stripe, y, color);
                    y++;
                }
            }
            stripe++;
        }
        i++;
    }
}