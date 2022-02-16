#include "cub3d.h"

// typedef struct s_var
// {
// 	double	transform_y;
// 	double	transform_x;
// 	int		draw_start_x;
// 	int		draw_end_x;
// 	int		draw_start_y;
// 	int		draw_end_y;
// 	int		sprite_screen_x;
// 	int		sprite_width;
// 	int		sprite_height;
// 	int		v_move_screen;
// }	t_var;
typedef struct s_sprites_param
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		tex_x;
	int		tex_y;
	int		color;
}	t_sprites_param;


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

void	sort_distance(int *nums, int *itrs, int size)
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

// void	calculation_distance(t_sprites *sprites, t_player *player)
// {
// 	int i;

// 	i = -1;
// 	while (++i < sprites->num)
// 	{
// 		sprites->distance[i] = (player->pos_x - sprites->coordinates[i].x)
// 			* (player->pos_x - sprites->coordinates[i].x)
// 			+ (player->pos_y - sprites->coordinates[i].y)
// 			* (player->pos_y - sprites->coordinates[i].y);
// 		sprites->iterator[i] = i;
// 	}
// }

// void	calculation_coller(t_sprites *sprites)
// {
// 	sprites->coller++;
// 	if (sprites->coller >= sprites->coller_max)
// 		sprites->coller = sprites->coller_min;
// }

// int	calculation_general_parameters(t_all *all, t_sprites_param *param, int i)
// {
// 	param->sprite_x = all->sprites.coordinates[i].x - all->player.pos_x;
// 	param->sprite_y = all->sprites.coordinates[i].y - all->player.pos_y;
// 	if (fabs(param->sprite_x) < 0.2 && fabs(param->sprite_y) < 0.2)
// 	{
// 		if (all->sprites.coordinates[i].texture_name == BARREL)
// 			all->sprites.coordinates[i].texture_flag = 1;
// 		return (FALSE);
// 	}
// 	param->inv_det = 1.0 / (all->player.plane_x * all->player.dir_y
// 		- all->player.dir_x * all->player.plane_y);
// 	param->transform_x = param->inv_det * (all->player.dir_y * param->sprite_x
// 		- all->player.dir_x * param->sprite_y);
// 	param->transform_y = param->inv_det * (-all->player.plane_y * param->sprite_x
// 		+ all->player.plane_x * param->sprite_y);
// 	param->sprite_screen_x = (int)((SCREEN_WIDTH / 2)
// 		* (1 + param->transform_x / param->transform_y));
// 	param->sprite_height = abs((int)(SCREEN_HEIGHT / param->transform_y));
// 	return (TRUE);
// }

// void	calculation_start_end(t_sprites_param *param)
// {
// 	param->draw_start_y = -param->sprite_height / 2 + SCREEN_HEIGHT / 2;
// 	if (param->draw_start_y < 0)
// 		param->draw_start_y = 0;
// 	param->draw_end_y = param->sprite_height / 2 + SCREEN_HEIGHT / 2;
// 	if (param->draw_end_y >= SCREEN_HEIGHT)
// 		param->draw_end_y = SCREEN_HEIGHT - 1;
// 	param->sprite_width = abs((int)(SCREEN_HEIGHT / param->transform_y));
// 	param->draw_start_x = -param->sprite_width / 2 + param->sprite_screen_x;
// 	if (param->draw_start_x < 0)
// 		param->draw_start_x = 0;
// 	param->draw_end_x = param->sprite_width / 2 + param->sprite_screen_x;
// 	if (param->draw_end_x > SCREEN_WIDTH)
// 		param->draw_end_x = SCREEN_WIDTH;
// }
/*
static void	draw_line(t_all *all, t_sprites_param *param, int y, t_data *pic)
{
	while (y < param->draw_end_y)
	{
		param->tex_y = (((y * 2 - (SCREEN_HEIGHT - param->sprite_height))
			* 128 * TEX_HEIGHT) / param->sprite_height) / 256;
		param->color = 0x000000;
		if (pic)
			param->color = my_mlx_pixel_get(pic, param->tex_x, param->tex_y);
		if (param->color != 0x000000)
			my_mlx_pixel_put(&all->img, param->draw_start_x, y, param->color);
		y++;
	}
}

static void	draw(t_all *all, t_sprites_param *param, int i)
{
	t_data	*picture;
	int		y;

	while (param->draw_start_x < param->draw_end_x)
	{
		y = param->draw_start_y;
		param->tex_x = (int)(256 * (param->draw_start_x - (-param->sprite_width / 2 + param->sprite_screen_x))
			* TEX_WIDTH / param->sprite_width) / 256;
		picture = NULL;
		if (all->sprites.coordinates[i].texture_name == BARREL)
			picture = &all->sprites.texture_barrel[all->sprites.coordinates[i].texture_flag];
		if (all->sprites.coordinates[i].texture_name == LIGHT)
			picture = &all->sprites.texture_light[all->sprites.coller / all->sprites.coller_mod];
		if (param->transform_y > 0 && param->transform_y < all->sprites.z_buffer[param->draw_start_x])
			draw_line(all, param, i, picture);
		param->draw_start_x++;
	}
}
*/
void	draw_sprites(t_all *all)
{
	t_sprites_param	param;
	int				i;
	int				j;

	calculation_distance(&all->sprites, &all->player);
	sort_distance(all->sprites.distance,
		all->sprites.iterator, all->sprites.num);
	calculation_coller(&all->sprites);

	j = all->sprites.num;
	while (--j >= 0)
	{
		i = all->sprites.iterator[j];
		if (calculation_general_parameters(all, &param, i) == FALSE)
			continue ;
		calculation_start_end(&param);
		// draw(all, &param, i);
	}
}
