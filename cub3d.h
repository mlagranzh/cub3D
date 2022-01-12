/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 15:41:43 by celys             #+#    #+#             */
/*   Updated: 2022/01/12 18:58:22 by cleonia          ###   ########.fr       */
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


#define CEL_SIZE 6
#define SCREEN_WIDTH 1280
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

typedef struct	s_player
{
	int		pos_x;				// Позиция по х
	int		pos_y;				// Позиция по у
	int		dir_x;				// Направление по х
	int		dir_y;				// Направление по у
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
	char		**map;
}	t_all;

void	draw_screen(t_all *all);

//map functions
int		read_map_param(t_map *map, int fd);
int		checking_map_for_closure(char **map);

//utils0
void	ft_change_sumbols_in_str(char *change_str, char *change_sumbols, char replacement_char);
int		print_return(int retval, char *print_message);
char	*delete_space_line(char *line);
void	printf_array(char **arr);

//utils1.c
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    draw_ver_line(t_all *all, int x, int draw_start, int draw_end, int color);
int	    destroy(t_all *all);
int     my_hook(int key, t_all *all);

//draw

#endif
