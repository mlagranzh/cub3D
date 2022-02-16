#include "cub3d.h"

typedef struct s_var
{
	double	transform_y;
	double	transform_x;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_screen_x;
	int		sprite_width;
	int		sprite_height;
	int		v_move_screen;
}	t_var;

int	perpendicular_walls(char **map, int i, int j)
{
	int	retval;

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

int	empty_lines(char **map, int i, int j)
{
	int	retval;

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

// static int	put(t_all *all, int i, int j)
// {
// 	static int	if_there_are = 0;
// 	static int	fact_sprites_num = 0;
// 	int 		ret;

// 	ret = 0;
// 	if (all->map.map[i][j] == '0')
// 	{
// 		if_there_are += perpendicular_walls(all->map.map, i, j);
// 		if_there_are += empty_lines(all->map.map, i, j);
// 		if (if_there_are > 0)
// 		{
// 			all->sprites.coordinates[fact_sprites_num].texture_name = \
// 															if_there_are;
// 			all->sprites.coordinates[fact_sprites_num].x = i + 0.5;
// 			all->sprites.coordinates[fact_sprites_num].y = j + 0.5;
// 			all->sprites.coordinates[fact_sprites_num].u_div = 1;
// 			all->sprites.coordinates[fact_sprites_num].v_div = 1;
// 			all->sprites.coordinates[fact_sprites_num].v_move = 0.0;
// 			all->sprites.coordinates[fact_sprites_num].texture_flag = 0;
// 			if_there_are = 0;
// 			fact_sprites_num++;
// 			ret++;
// 		}
// 		if_there_are = 0;
// 		fact_sprites_num++;
// 		ret++;
// 	}
// 	return (ret);
// }

// void	put_sprites_on_map(t_all *all, t_map *map)
// {
// 	int	i;
// 	int	j;
// 	int	fact_sprites_num;
// 	int	if_there_are;

// 	i = -1;
// 	fact_sprites_num = 0;
// 	if_there_are = 0;
// 	while (map->map[++i])
// 	{
// 		j = 0;
// 		while (map->map[i][j] != '\0')
// 		{
// 			fact_sprites_num += put(all, i, j);
// 				if (fact_sprites_num == all->sprites.num)
// 					return ;
// 			j++;
// 		}
// 	}
// 	all->sprites.num = fact_sprites_num;
// }

void	put_sprites_on_map(t_all *all, t_map *map)
{
	int	i;
	int	j;
	int	fact_sprites_num;
	int	if_there_are;

	i = -1;
	fact_sprites_num = 0;
	if_there_are = 0;
	while (map->map[++i])
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
					all->sprites.coordinates[fact_sprites_num].texture_name = \
																if_there_are;
					all->sprites.coordinates[fact_sprites_num].x = i + 0.5;
					all->sprites.coordinates[fact_sprites_num].y = j + 0.5;
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
	}
    all->sprites.num = fact_sprites_num;
}

void	sprites_init(t_all *all)
{
	all->sprites.num = 20;
	all->sprites.z_buffer = malloc(sizeof(double) * SCREEN_WIDTH);
	all->sprites.coordinates = malloc(sizeof(t_coordinate) * all->sprites.num);
	all->sprites.texture_barrel = (t_data *)malloc(sizeof(t_data) * 2);
	image_load(all, &all->sprites.texture_barrel[0], BARREL_WHOLE);
	image_load(all, &all->sprites.texture_barrel[1], BARREL_RUINED);
	all->sprites.texture_light = (t_data *)malloc(sizeof(t_data) * 3);
	image_load(all, &all->sprites.texture_light[0], ELLOW_LIGHT);
	image_load(all, &all->sprites.texture_light[1], RED_LIGHT);
	image_load(all, &all->sprites.texture_light[2], BLACK_LIGHT);
	all->sprites.coller = 0;
	all->sprites.coller_max = 89;
	all->sprites.coller_min = 0;
	all->sprites.coller_mod = 45;
	put_sprites_on_map(all, &all->map);
	all->sprites.distance = malloc(sizeof(int) * all->sprites.num);
	all->sprites.iterator = malloc(sizeof(int) * all->sprites.num);
}

void	bubble_sort(int *nums, int *itrs, int size)
{
	int	temp;
	int	i;
	int	j;

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

void 	funct(t_all *all)
{
	int		i;
	double	x;
	double	y;

	i = -1;
	while (++i < all->sprites.num)
	{
		x = pow((all->player.pos_x - all->sprites.coordinates[i].x), 2);
		y = pow((all->player.pos_y - all->sprites.coordinates[i].y), 2);
		all->sprites.distance[i] = x + y;
		all->sprites.iterator[i] = i;
	}
	bubble_sort(all->sprites.distance, all->sprites.iterator, all->sprites.num);
	all->sprites.coller++;
	if (all->sprites.coller >= all->sprites.coller_max)
		all->sprites.coller = all->sprites.coller_min;
}

void	draw(t_all *all, t_var *vars, int i)
{
	int	stripe;
	int	tex_x;
	int	tex_y;
	int	y;
	int	d;
	int color;

	stripe = vars->draw_start_x - 1;
	while (++stripe < vars->draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-vars->sprite_width / 2 + \
			vars->sprite_screen_x)) * TEX_WIDTH / vars->sprite_width) / 256;
		if (vars->transform_y > 0 && \
				vars->transform_y < all->sprites.z_buffer[stripe])
		{
			y = vars->draw_start_y - 1;
			while (++y < vars->draw_end_y)
			{
				d = (y - vars->v_move_screen) * 256 - SCREEN_HEIGHT * 128 + vars->sprite_height * 128;
				tex_y = ((d * TEX_HEIGHT) / vars->sprite_height) / 256;
				color = 0x000000;
				if (all->sprites.coordinates[i].texture_name == BARREL)
					color = my_mlx_pixel_get(&all->sprites.texture_barrel[all->sprites.coordinates[i].texture_flag], tex_x, tex_y);
				if (all->sprites.coordinates[i].texture_name == LIGHT)
                	color = my_mlx_pixel_get(&all->sprites.texture_light[all->sprites.coller / all->sprites.coller_mod], tex_x, tex_y);
				if (color != 0x000000)
					my_mlx_pixel_put(&all->img, stripe, y, color);
			}
		}
	}
}

void	init(t_all *all, t_var *vars, int i)
{
	double	inv_det;
	double	sprite_x;
	double	sprite_y;

	sprite_x = all->sprites.coordinates[i].x - all->player.pos_x;
	sprite_y = all->sprites.coordinates[i].y - all->player.pos_y;
	if (fabs(sprite_x) < 0.2 && fabs(sprite_y) < 0.2)
	{
		if (all->sprites.coordinates[i].texture_name == BARREL)
			all->sprites.coordinates[i].texture_flag = 1;
	}
	inv_det = 1.0 / (all->player.plane_x * all->player.dir_y - \
					all->player.dir_x * all->player.plane_y);
	vars->transform_x = inv_det * \
		(all->player.dir_y * sprite_x - all->player.dir_x * sprite_y);
	vars->transform_y = inv_det * \
		(-all->player.plane_y * sprite_x + all->player.plane_x * sprite_y);
	vars->sprite_screen_x = (int)((SCREEN_WIDTH / 2) * \
						(1 + vars->transform_x / vars->transform_y));
	vars->v_move_screen = (int)(all->sprites.coordinates[i].v_move / \
							vars->transform_y);
	vars->sprite_height = abs((int)(SCREEN_HEIGHT / vars->transform_y)) / \
								all->sprites.coordinates[i].v_div;
	vars->draw_start_y = -vars->sprite_height / 2 + \
						SCREEN_HEIGHT / 2 + vars->v_move_screen;
	if (vars->draw_start_y < 0)
		vars->draw_start_y = 0;
	vars->draw_end_y = vars->sprite_height / 2 + SCREEN_HEIGHT / 2 + \
							vars->v_move_screen;
	if (vars->draw_end_y >= SCREEN_HEIGHT)
		vars->draw_end_y = SCREEN_HEIGHT - 1;
	vars->sprite_width = abs((int)(SCREEN_HEIGHT / vars->transform_y)) / \
			all->sprites.coordinates[i].u_div;
	vars->draw_start_x = -vars->sprite_width / 2 + vars->sprite_screen_x;
	if (vars->draw_start_x < 0)
		vars->draw_start_x = 0;
	vars->draw_end_x = vars->sprite_width / 2 + vars->sprite_screen_x;
	if (vars->draw_end_x > SCREEN_WIDTH)
		vars->draw_end_x = SCREEN_WIDTH;
}

void	draw_sprites(t_all *all)
{
	int		j;
	int 	i;
	t_var	vars;

	funct(all);
	j = all->sprites.num;
	while (--j >= 0)
	{
		i = all->sprites.iterator[j];
		init(all, &vars, i);
		draw(all, &vars, i);
	}
}
