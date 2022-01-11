/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 15:41:43 by celys             #+#    #+#             */
/*   Updated: 2022/01/12 02:38:22 by celys            ###   ########.fr       */
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

typedef struct s_all
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_player	player;
	char		**map;
	double		pos_x;
	double		pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
}	t_all;


//utils0
char **ft_realloc(char **mas, char *new_line);
char *delete_space_line(char *line);
void printf_array(char **arr);

//utils1.c
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    draw_ver_line(t_all *all, int x, int draw_start, int draw_end, int color);
int	    destroy(t_all *all);
int     my_hook(int key, t_all *all);

//draw
void	draw_map(t_data *img, char **map);
void	draw_screen(t_all *all);
void	draw_square(t_data *img, int y, int x, int size);
void	draw_player(t_all *all);
#endif
