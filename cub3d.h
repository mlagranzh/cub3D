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

#define CEL_SIZE 6
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

enum    e_retvals
{
    ERROR = 1,
    SUCCESS = 0
};

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_wall
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_wall;

typedef struct	s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;
}	t_player;

typedef struct s_map
{
	char	*no_texture; 		// Север	(90)
	char	*so_texture; 		// Юг 		(270)
	char	*we_texture; 		// Запад 	(180)
	char	*ea_texture; 		// Восток 	(0)
	int		floor_color[3]; 	// Пол
	int		ceilling_color[3];	// Потолок
	char	**map;
}	t_map;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_player	player;
	t_wall		wall;
	t_map		map;
}	t_all;

void	ft_print_cchar(char **mas);

//map functions
int		read_map_param(t_map *map, int fd);
int		checking_map_for_closure(char **map);
int		read_cub_file(t_map *map, t_player *player, char *file_name);

//utils0
void	ft_change_sumbols_in_str(char *change_str, char *change_sumbols, char replacement_char);
int		print_return(int retval, char *print_message);
char	*delete_space_line(char *line);
void	printf_array(char **arr);
char **ft_realloc(char **mas, char *new_line);

//utils1.c
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    draw_ver_line(t_all *all, int x, int draw_start, int draw_end, int color);
int	    destroy(t_all *all);
int     my_hook(int key, t_all *all);

//utils2
int get_hex(int r, int g, int b);
int ft_abs(int num);


//draw
void	draw_map(t_data *img, char **map);
void	draw_screen(t_all *all);
void	draw_square(t_data *img, int y, int x, int size);
void	draw_player(t_all *all);


char	*texture_load(t_all *all);
void draw_wall(t_all *all, int mapX, int mapY, int side, int perpWallDist, \
                double rayDirX, double rayDirY, int lineHeight, int drawStart, int drawEnd, int x, \
                char	*texture);

#endif
