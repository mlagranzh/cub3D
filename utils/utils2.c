/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:29:52 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/15 17:48:10 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	my_mlx_pixel_get(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_square(t_data *img, int y, int x, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < CEL_SIZE)
	{
		j = 0;
		while (j < CEL_SIZE)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_border_square(t_data *img, t_square_param param)
{
	int	i;
	int	j;

	i = 0;
	while (i < param.size)
	{
		j = -1;
		while (++j < param.size)
		{
			if (param.x + i < 0 || param.y + j < 0
				|| param.x + i > SCREEN_WIDTH || param.y + j > SCREEN_HEIGHT)
				continue ;
			if (i == 0 || j == 0 || i == param.size - 1 || j == param.size - 1)
				my_mlx_pixel_put(img, param.x + i,
					param.y + j, param.border_color);
			else
				my_mlx_pixel_put(img, param.x + i,
					param.y + j, param.inside_color);
		}
		i++;
	}
}

void	draw_border_centre_square(t_data *img, t_square_param param)
{
	int	i;
	int	j;

	i = param.x - param.size;
	while (i <= param.x + param.size)
	{
		j = param.y - param.size - 1;
		while (++j <= param.y + param.size)
		{
			if (i < 0 || j < 0)
				continue ;
			if (i == param.x - param.size || j == param.y - param.size
				|| i == param.x + param.size || j == param.y + param.size)
				my_mlx_pixel_put(img, i, j, param.border_color);
			else
				my_mlx_pixel_put(img, i, j, param.inside_color);
		}
		i++;
	}
}
