#include "cub3d.h"


void draw_wall()
{
    
}


void	texture_load(t_env *e)
{
	int		width;
	int		height;

	e->wall[0] = mlx_xpm_file_to_image(e->mlx,
			"gfx/floor.xpm", &width, &height);
}