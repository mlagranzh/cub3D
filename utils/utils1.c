/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:28:52 by celys             #+#    #+#             */
/*   Updated: 2022/01/11 18:32:10 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		my_hook(int key, t_all *all)
{
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
	return (0);
}

int	destroy(t_all *all)
{
	exit (0);
	return (0);
}

void draw_ver_line(t_all *all, int x, int draw_start, int draw_end, int color)
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
	*(unsigned int*)dst = color;
}