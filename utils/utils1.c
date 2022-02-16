/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:49:09 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/16 04:54:50 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	image_load(t_all *all, t_data *data, char	*path)
{
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
