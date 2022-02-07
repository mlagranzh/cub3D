unsigned char	get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}

// #include "cub3d.h"

// void draw_sprites(t_all *all, int col)
// {
//     int i;

//     i = 0;
//     while (i < SPRITES_NUM)
//     {
//         // printf("\n\n-------FACK-------\n");
//         double sprite_x = sprites[i].x - all->player.pos_x;
//         double sprite_y = sprites[i].y - all->player.pos_y;

//         if (fabs(sprite_x) < 0.2 && fabs(sprite_y) < 0.2)
//         {
//             i++;
//             continue ;
//         }

//         // printf("sprite x/y = %f/%f\n", sprite_x, sprite_y);

//         double inv_det = 1.0 / (all->player.plane_x * all->player.dir_y
//             - all->player.dir_x * all->player.plane_y);

//         // printf("inv_det = %f\n", inv_det);
        
//         double transform_x = inv_det * (all->player.dir_y * sprite_x - all->player.dir_x * sprite_y);
//         double transform_y = inv_det * (-all->player.plane_y * sprite_x + all->player.plane_x * sprite_y);

//         // printf("transofrm x/y = %f/%f\n", transform_x, transform_y);

//         int sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + transform_x / transform_y));

//         // printf("screen_x = %i\n", sprite_screen_x);

//         #define U_DIV 1
//         #define V_DIV 1
//         #define V_MOVE 0.0

//         int v_move_screen = (int)(V_MOVE / transform_y);

//         // printf("v_move_screen = %i\n", v_move_screen);

//         int sprite_height = abs((int)(SCREEN_HEIGHT / transform_y)) / (V_DIV + col / 30);

//         // printf("sprite_height = %i\n", sprite_height);

//         int draw_start_y = -sprite_height / 2 + SCREEN_HEIGHT / 2 + v_move_screen;
//         if (draw_start_y < 0)
//             draw_start_y = 0;
//         int draw_end_y = sprite_height / 2 + SCREEN_HEIGHT / 2 + v_move_screen;
//         if (draw_end_y >= SCREEN_HEIGHT)
//             draw_end_y = SCREEN_HEIGHT - 1;

//         // printf("start/end y = %i/%i\n", draw_start_y, draw_end_y);

//         int sprite_width = abs((int)(SCREEN_HEIGHT / transform_y)) / U_DIV;

//         // printf("sprite_width = %i\n", sprite_width);

//         int draw_start_x = -sprite_width / 2 + sprite_screen_x;
//         if (draw_start_x < 0)
//             draw_start_x = 0;
//         int draw_end_x = sprite_width / 2 + sprite_screen_x;
//         if (draw_end_x > SCREEN_WIDTH)
//             draw_end_x = SCREEN_WIDTH;

//         // printf("start/end x = %i/%i\n", draw_start_x, draw_end_x);
        
//         int stripe = draw_start_x;
//         while (stripe < draw_end_x)
//         {
//             int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x))
//                 * texWidth / sprite_width) / 256;
//             // printf("tex_x %i;", tex_x);

//             if (transform_y > 0 && (int)transform_y <= all->z_buffer[stripe])
//             {
//                 int y = draw_start_y;
//                 while (y < draw_end_y)
//                 {
//                     int d = (y - v_move_screen) * 256 - SCREEN_HEIGHT * 128 + sprite_height * 128;
//                     int tex_y = ((d * texHeight) / sprite_height) / 256;
//                     // printf("%i / ", tex_y);
//                     int color = my_mlx_pixel_get(sprites[i].texture, tex_x, tex_y);
//                     if (color != 0x000000)
//                         my_mlx_pixel_put(&all->img, stripe, y, color - col);
//                     y++;
//                 }
//             }
//             stripe++;
//         }
//         // printf("\n");
//         i++;
//     }
// }
