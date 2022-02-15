/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:49:09 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/15 17:51:12 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_ver_line(t_all *all, int x, int draw_start, int draw_end, int color)
{
	while (draw_start < draw_end)
	{
		my_mlx_pixel_put(&all->img, x, draw_start, color);
		draw_start++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	image_load(t_all *all, t_data *data, char	*path)
{
	void	*img;
	int		img_width;
	int		img_height;

	data->img = mlx_xpm_file_to_image(all->mlx, path, &img_width, &img_height);
	if (data->img == NULL)
	{
		write(2, "Texture error!\n", 16);
		exit(1);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}
