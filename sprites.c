#include "cub3d.h"


int perpendicular_walls(char **map, int i, int j)
{
    int retval;

    retval = 0;
    if (map[i - 1][j] == '1')
        retval++;
    if (map[i + 1][j] == '1')
        retval++;
    if (map[i][j - 1] == '1')
        retval++;
    if (map[i][j + 1] == '1')
        retval++;
    if (retval == 3)
        return (BARREL);
    return (0);
}

int empty_lines(char **map, int i, int j)
{
    int retval;

    retval = 0;
    if (map[i - 1][j] == '0' && map[i - 2][j] == '0' && map[i - 3][j])
        retval++;
    if (map[i + 1][j] == '0' && map[i + 2][j] == '0' && map[i + 3][j])
        retval++;
    if (map[i][j - 1] == '0' && map[i][j - 2] == '0' && map[i][j - 3] == '0')
        retval++;
    if (map[i][j + 1] == '0' && map[i][j + 2] == '0' && map[i][j + 3] == '0')
        retval++;
    if (retval == 4)
        return (LIGHT);
    return (0);
}

void put_sprites_on_map(t_all *all, t_map *map)
{
	int i;
	int j;
    int fact_sprites_num;
    int if_there_are;

	i = 0;
    fact_sprites_num = 0;
    if_there_are = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] == '0')
			{
                if_there_are += perpendicular_walls(map->map, i, j);
                if_there_are += empty_lines(map->map, i, j);
				if (if_there_are > 0)
				{
                    all->sprites.coordinates[fact_sprites_num].texture_name = if_there_are;
                    all->sprites.coordinates[fact_sprites_num].x = (double)i + 0.5;
                    all->sprites.coordinates[fact_sprites_num].y = (double)j + 0.5;
            	    all->sprites.coordinates[fact_sprites_num].u_div = 1;
	                all->sprites.coordinates[fact_sprites_num].v_div = 1;
	                all->sprites.coordinates[fact_sprites_num].v_move = 0.0;
	                all->sprites.coordinates[fact_sprites_num].texture_flag = 0;
                    if_there_are = 0;
                    fact_sprites_num++;
				}
                if (fact_sprites_num == all->sprites.num)
                    return ;
			}
			j++;
		}
		i++;
	}
    all->sprites.num = fact_sprites_num;
    // printf("%i\n", all->sprites.num);
}

void sprites_init(t_all *all)
{
	all->sprites.num = 20;

	all->sprites.z_buffer = (double *)malloc(sizeof(double) * SCREEN_WIDTH);

	all->sprites.coordinates = (t_coordinate *)malloc(sizeof(t_coordinate) * all->sprites.num);

	all->sprites.texture_barrel = (t_data *)malloc(sizeof(t_data) * 2);
	texture_load(all, &all->sprites.texture_barrel[0], "textures/barrel_whole.xpm");
	texture_load(all, &all->sprites.texture_barrel[1], "textures/barrel_ruined.xpm");
	
	all->sprites.texture_light = (t_data *)malloc(sizeof(t_data) * 3);
	texture_load(all, &all->sprites.texture_light[0], "textures/ellowlight.xpm");
	texture_load(all, &all->sprites.texture_light[1], "textures/redlight.xpm");
	texture_load(all, &all->sprites.texture_light[2], "textures/blacklight.xpm");

	all->sprites.coller = 0;
	all->sprites.coller_max = 89;
	all->sprites.coller_min = 0;
	all->sprites.coller_mod = 45;

	put_sprites_on_map(all, &all->map);

    all->sprites.distance = (int *)malloc(sizeof(int) * all->sprites.num);
    all->sprites.iterator = (int *)malloc(sizeof(int) * all->sprites.num);
}

void bubble_sort(int *nums, int *itrs, int size)
{
    int temp;
    int i;
    int j;

    i = 0;
    while (i < size - 1)
    {
        j = size - 1;
        while (j > i)
        {
            if (nums[j - 1] > nums[j])
            {
                temp = nums[j - 1];
                nums[j - 1] = nums[j];
                nums[j] = temp;
                temp = itrs[j - 1];
                itrs[j - 1] = itrs[j];
                itrs[j] = temp;
            }
            j--;
        }
        i++;
    }
}

void draw_sprites(t_all *all)
{
    int i;
    int j;

    /* sort */
    i = 0;
    while (i < all->sprites.num)
    {
        all->sprites.distance[i] = (all->player.pos_x - all->sprites.coordinates[i].x) * (all->player.pos_x - all->sprites.coordinates[i].x)
            + (all->player.pos_y - all->sprites.coordinates[i].y) * (all->player.pos_y - all->sprites.coordinates[i].y);
        all->sprites.iterator[i] = i;
        i++;
    }

    bubble_sort(all->sprites.distance, all->sprites.iterator, all->sprites.num);

    all->sprites.coller++;
    if (all->sprites.coller >= all->sprites.coller_max)
        all->sprites.coller = all->sprites.coller_min;
    // printf("coller = %i\n", all->sprites.coller / all->sprites.coller_mod);
    j = all->sprites.num;
    while (--j >= 0)
    {
        i = all->sprites.iterator[j];
        // printf("\n\n-------FACK-------\n");
        double sprite_x = all->sprites.coordinates[i].x - all->player.pos_x;//sprites[i].x - all->player.pos_x;
        double sprite_y = all->sprites.coordinates[i].y - all->player.pos_y;//sprites[i].y - all->player.pos_y;

        if (fabs(sprite_x) < 0.2 && fabs(sprite_y) < 0.2)
        {
            if (all->sprites.coordinates[i].texture_name == BARREL)
                all->sprites.coordinates[i].texture_flag = 1;
            continue ;
        }
        // printf("sprite x/y = %f/%f\n", sprite_x, sprite_y);

        double inv_det = 1.0 / (all->player.plane_x * all->player.dir_y
            - all->player.dir_x * all->player.plane_y);

        // printf("inv_det = %f\n", inv_det);
        
        double transform_x = inv_det * (all->player.dir_y * sprite_x - all->player.dir_x * sprite_y);
        double transform_y = inv_det * (-all->player.plane_y * sprite_x + all->player.plane_x * sprite_y);

        // printf("transofrm x/y = %f/%f\n", transform_x, transform_y);

        int sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + transform_x / transform_y));

        // printf("screen_x = %i\n", sprite_screen_x);

        int v_move_screen = (int)(all->sprites.coordinates[i].v_move / transform_y);

        // printf("v_move_screen = %i\n", v_move_screen);

        int sprite_height = abs((int)(SCREEN_HEIGHT / transform_y)) / all->sprites.coordinates[i].v_div;

        // printf("sprite_height = %i\n", sprite_height);

        int draw_start_y = -sprite_height / 2 + SCREEN_HEIGHT / 2 + v_move_screen;
        if (draw_start_y < 0)
            draw_start_y = 0;
        int draw_end_y = sprite_height / 2 + SCREEN_HEIGHT / 2 + v_move_screen;
        if (draw_end_y >= SCREEN_HEIGHT)
            draw_end_y = SCREEN_HEIGHT - 1;

        // printf("start/end y = %i/%i\n", draw_start_y, draw_end_y);

        int sprite_width = abs((int)(SCREEN_HEIGHT / transform_y)) / all->sprites.coordinates[i].u_div;

        // printf("sprite_width = %i\n", sprite_width);

        int draw_start_x = -sprite_width / 2 + sprite_screen_x;
        if (draw_start_x < 0)
            draw_start_x = 0;
        int draw_end_x = sprite_width / 2 + sprite_screen_x;
        if (draw_end_x > SCREEN_WIDTH)
            draw_end_x = SCREEN_WIDTH;

        // printf("start/end x = %i/%i\n", draw_start_x, draw_end_x);
        
        int stripe = draw_start_x;
        while (stripe < draw_end_x)
        {
            int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x))
                * texWidth / sprite_width) / 256;
            
            if (transform_y > 0 && transform_y < all->sprites.z_buffer[stripe])
            {
                int y = draw_start_y;
                while (y < draw_end_y)
                {
                    int d = (y - v_move_screen) * 256 - SCREEN_HEIGHT * 128 + sprite_height * 128;
                    int tex_y = ((d * texHeight) / sprite_height) / 256;
                    int color = 0x000000;
                    if (all->sprites.coordinates[i].texture_name == BARREL)
                        color = my_mlx_pixel_get(&all->sprites.texture_barrel[all->sprites.coordinates[i].texture_flag], tex_x, tex_y);
                    if (all->sprites.coordinates[i].texture_name == LIGHT)
                        color = my_mlx_pixel_get(&all->sprites.texture_light[all->sprites.coller / all->sprites.coller_mod], tex_x, tex_y);
                    if (color != 0x000000)
                        my_mlx_pixel_put(&all->img, stripe, y, color);
                    y++;
                }
            }
            stripe++;
        }
    }
}
