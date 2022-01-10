/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 15:41:43 by celys             #+#    #+#             */
/*   Updated: 2022/01/10 18:19:14 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define CEL_SIZE 16
#define WIDTH 480
#define HEIGHT 320

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
	int	x;
	int y;
	int color;
}	t_player;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_player	player;
	char		**map;
}	t_all;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	destroy(t_all *all)
{
	exit (0);
	return (0);
}

char **ft_realloc(char **mas, char *new_line)
{
	char **new_mas;
	int mas_len;
	int i;

	if (!mas)
	{
		mas_len = 2;
		new_mas = (char **)malloc(sizeof(char *) * mas_len);
		new_mas[0] = new_line;
		new_mas[1] = NULL;
	}
	else
	{
		mas_len = 0;
		while (mas && mas[mas_len])
			mas_len++;
		mas_len++;
		new_mas = (char **)malloc(sizeof(char *) * (mas_len + 1));
		i = -1;
		while (++i < mas_len - 1)
			new_mas[i] = mas[i];
		new_mas[i] = new_line;
		new_mas[i + 1] = NULL;
		free (mas);
	}
	return (new_mas);
}

void	ft_print_cchar(char **mas)
{
	int i = 0;

	while(mas[i])
	{
		printf("%s\n", mas[i]);
		i++;
	}
	// printf("%s\n", mas[i]);
}

char **make_map(char *file_name)
{
	char *line;
	char **map;
	int fd;
	int i;

	fd = open(file_name, O_RDONLY);
	line = NULL;
	map = NULL;
	i = 1;
	while (get_next_line(fd, &line) == 1)
	{
		map = ft_realloc(map, line);
		i++;
	}
	// ft_print_cchar(map);
	return (map);
}

void	draw_square(t_data *img, int y, int x, int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, x * size + i, y * size + j, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *img, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(img, i, j, CEL_SIZE);
			j++;
		}
		i++;
	}
}

void	draw_player(t_all *all)
{
	int i;
	int j;
	int size;

	i = 0;
	size = 4;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(&(all->img), all->player.x + i, all->player.y + j, 0xFF00FF);
			j++;
		}
		i++;
	}
	float player_a = 0;
	float start = player_a - 3.14/4;
	float end = player_a + 3.14/4;
	while (start < end)
	{
		float x_2 = all->player.x;
		float y_2 = all->player.y;
		while (all->map[(int)(y_2/CEL_SIZE)][(int)(x_2/CEL_SIZE)] != '1')
		{
			x_2 += cos(start);
			y_2 += sin(start);
			my_mlx_pixel_put(&all->img, x_2, y_2, 0xFF00FF);
		}
		start += 3.14/20;
	}
}

int		my_hook(int key, t_all *all)
{
	mlx_clear_window(all->mlx, all->win);
	if (key == 13)
		all->player.y -= 4;
	if (key == 1)
		all->player.y += 4;
	if (key == 0)
		all->player.x -= 4;
	if (key == 2)
		all->player.x += 4;
	if (key == 53)
		exit(0);
	all->img.img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length, &all->img.endian);
	draw_map(&(all->img), all->map);
	draw_player(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (0);
}

int main()
{
	t_all	all;

	all.mlx = mlx_init();
	all.map = make_map("map.cub");
	all.win = mlx_new_window(all.mlx, WIDTH, HEIGHT, "cub");
	all.img.img = mlx_new_image(all.mlx, WIDTH, HEIGHT);
	all.img.addr = mlx_get_data_addr(all.img.img, &all.img.bits_per_pixel, &all.img.line_length, &all.img.endian);

	draw_map(&all.img, all.map);

	all.player.x = 100;
	all.player.y = 100;
	all.player.color = 0xFF00FF;
	draw_player(&all);

	mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);

	mlx_hook(all.win, 2, 1L << 2, my_hook, (void *)&all);
	mlx_hook(all.win, 17, 0L, destroy, (void *)&all);
	mlx_loop(all.mlx);
	return (0);
}