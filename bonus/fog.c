#include "../cub3d.h"

# define FOG_COLOR 9802646

static void	put_fog_on_color(int *color, double fog_percent)
{
	int red;
	int green;
	int blue;
	double color_percent;

	color_percent = 1. - fog_percent;
    red = get_r(*color) * color_percent + fog_percent * get_r(FOG_COLOR);
	green = get_g(*color) * color_percent + fog_percent * get_g(FOG_COLOR);
	blue = get_b(*color) * color_percent + fog_percent * get_b(FOG_COLOR);
	*color = create_trgb(0, red, green, blue);
}

static void	put_fog_on_texture(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (++y < TEX_HEIGHT)
	{
		x = -1;
		while (++x < TEX_WIDTH)
		{
			color = my_mlx_pixel_get(data, x, y);
            if (color == 0x000000)
                continue;
            put_fog_on_color(&color, 0.95);
            my_mlx_pixel_put(data, x, y, color);
		}
	}
}

void fog_init(t_all *all)
{
	all->fog.flag = 0;

	all->fog.clear_wall = all->wall;
	all->fog.clear_barrel = all->sprites.texture_barrel;
	all->fog.clear_floor = all->map.floor_color;
	all->fog.clear_ceilling = all->map.ceilling_color;

	all->fog.fog_wall = (t_data *)malloc(sizeof(t_data) * 4);
	image_load(all, &all->fog.fog_wall[0], all->map.no_texture);
	image_load(all, &all->fog.fog_wall[1], all->map.so_texture);
	image_load(all, &all->fog.fog_wall[2], all->map.we_texture);
	image_load(all, &all->fog.fog_wall[3], all->map.ea_texture);
	put_fog_on_texture(&all->fog.fog_wall[0]);
	put_fog_on_texture(&all->fog.fog_wall[1]);
	put_fog_on_texture(&all->fog.fog_wall[2]);
	put_fog_on_texture(&all->fog.fog_wall[3]);

	all->fog.fog_barrel = (t_data *)malloc(sizeof(t_data) * 2);
	image_load(all, &all->fog.fog_barrel[0], BARREL_WHOLE);
	image_load(all, &all->fog.fog_barrel[1], BARREL_RUINED);
	put_fog_on_texture(&all->fog.fog_barrel[0]);
	put_fog_on_texture(&all->fog.fog_barrel[1]);

	all->fog.fog_floor = all->map.floor_color;
	all->fog.fog_ceilling = all->map.ceilling_color;
	put_fog_on_color(&all->fog.fog_floor, 0.75);
	put_fog_on_color(&all->fog.fog_ceilling, 0.75);
}

void fog(t_all *all)
{
    if (all->fog.flag == 0)
    {
        all->wall = all->fog.fog_wall;
        all->sprites.texture_barrel = all->fog.fog_barrel;
        all->map.floor_color = all->fog.fog_floor;
        all->map.ceilling_color = all->fog.fog_ceilling;
        all->fog.flag = 1;
    }
    else
    {
        all->wall = all->fog.clear_wall;
        all->sprites.texture_barrel = all->fog.clear_barrel;
        all->map.floor_color = all->fog.clear_floor;
        all->map.ceilling_color = all->fog.clear_ceilling;
        all->fog.flag = 0;
    }
}