/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:16:40 by celys             #+#    #+#             */
/*   Updated: 2022/02/16 01:17:50 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>
# include <limits.h>

# define KEY_LEFT			123
# define KEY_RIGHT			124
# define KEY_UP				126
# define KEY_DOWAN			125
# define KEY_W				13
# define KEY_S				1
# define KEY_D				2
# define KEY_A				0
# define KEY_ESC			53
# define KEY_SPACE			49
# define KEY_ENTER			36
# define KEY_FN_F12			111

# define CEL_SIZE 6
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 600
# define TEX_WIDTH 64.
# define TEX_HEIGHT 64.

# define ROTATE_SPEED 0.3
# define MOVE_SPEED 0.5

# define BARREL_WHOLE "textures/barrel_whole.xpm"
# define BARREL_RUINED "textures/barrel_ruined.xpm"
# define ELLOW_LIGHT "textures/ellowlight.xpm"
# define RED_LIGHT "textures/redlight.xpm"
# define BLACK_LIGHT "textures/blacklight.xpm"

enum	e_retvals
{
	ERROR = 1,
	SUCCESS = 0,
	TRUE = 1,
	FALSE = 0
};

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	start_side;
	int		mouse_x;
}	t_player;

typedef struct s_map
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceilling_color;
	char	**map;
	int		width;
	int		height;
}	t_map;

enum	e_textures_name
{
	BARREL = 1,
	LIGHT = 2
};

typedef struct s_sprite_coordinate
{
	double		x;
	double		y;
	int			u_div;
	int			v_div;
	double		v_move;
	int			texture_flag;
	int			texture_name;
}	t_coordinate;

typedef struct s_sprites
{
	t_data			*texture_light;
	t_data			*texture_barrel;
	int				coller;
	int				coller_max;
	int				coller_min;
	int				coller_mod;
	t_coordinate	*coordinates;
	int				num;
	int				*distance;
	int				*iterator;
	double			*z_buffer;
}	t_sprites;

typedef struct s_fog
{
	int		flag;

	t_data	*clear_wall;
	t_data	*clear_barrel;
	int		clear_floor;
	int		clear_ceilling;

	t_data	*fog_wall;
	t_data	*fog_barrel;
	int		fog_floor;
	int		fog_ceilling;
}	t_fog;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_data		*wall;
	t_player	player;
	t_map		map;
	t_sprites	sprites;
	t_fog		fog;
}	t_all;

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		draw_start;
	int		draw_end;
	int		line_height;
}	t_raycast;

void	ft_print_cchar(char **mas);

//map functions
int		cub_file(t_map *map, t_player *player, char *file_name);
int		checking_map_for_closure(char **map);

//utils0
void	ft_change_sumbols_in_str(char *change_str, char *change_sumbols, char replacement_char);
int		print_return(int retval, char *print_message);
void	printf_array(char **arr);
void	replace(double *x, double x_new, double *y, double y_new);

//utils1.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		destroy(t_all *all);
void	image_load(t_all *all, t_data *data, char	*path);

//utils2
int		my_mlx_pixel_get(t_data *data, int x, int y);

//utils3
int		free_2d_int(int **p, size_t size);
char	*my_strjoin(char *s1, char *s2, char *s3);
int		free_2d_char(char **p);

// utils4
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);
int		create_trgb(int t, int r, int g, int b);

//motion
void	move_straight(int key, t_all *all);
void	move_side(int key, t_all *all);

void	rotate(int key, t_all *all, double rotSpeed);

//draw_minimap
void	draw_minimap(t_all *all);

//draw_screen
void	draw_screen(t_all *all);

//hook
int		loop_hook(t_all *all);
int		mouse_hook(int x, int y, t_all *all);
int		my_hook(int key, t_all *all);
void	cub_destroy(t_all *all);


//sprites
void	draw_sprites(t_all *all);
void	sprites_init(t_all *all);

// fog
int		fog_init(t_all *all);
void	fog(t_all *all);

//screenshot
void screenshot(t_all *all);

//texture
void	draw_wall(t_all *all, t_raycast *raycast, int x);

#endif
