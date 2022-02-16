/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:51:35 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/16 21:43:46 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	printf_array_int(int *arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		printf("%d\n", arr[i]);
}

void	printf_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
}

int	print_return(int retval, char *print_message)
{
	printf("%s\n", print_message);
	return (retval);
}

void	replace(double *x, double x_new, double *y, double y_new)
{
	*x = x_new;
	*y = y_new;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
