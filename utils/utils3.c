/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 22:03:31 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/17 03:20:21 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_raycast(int x, t_all *all, t_raycast *raycast)
{
	raycast->camera_x = 2. * (double)x / (double)SCREEN_WIDTH - 1.;
	raycast->ray_dir_x = all->player.dir_x + all->player.plane_x \
											* raycast->camera_x;
	raycast->ray_dir_y = all->player.dir_y + all->player.plane_y \
											* raycast->camera_x;
	raycast->map_x = (int)all->player.pos_x;
	raycast->map_y = (int)all->player.pos_y;
	if (raycast->ray_dir_x == 0)
		raycast->delta_dist_x = 1e30;
	else
		raycast->delta_dist_x = fabs(1 / raycast->ray_dir_x);
	if (raycast->ray_dir_y == 0)
		raycast->delta_dist_y = 1e30;
	else
		raycast->delta_dist_y = fabs(1 / raycast->ray_dir_y);
	raycast->hit = 0;
}

int	len_int(int *array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != -1)
		i++;
	return (i);
}

int	ft_itoa_base_count(unsigned long int nb, unsigned int base)
{
	int	i;

	if (nb == 0)
		return (1);
	i = 0;
	while (nb)
	{
		nb = nb / base;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(unsigned long int nb, unsigned int base)
{
	char	*ret;
	char	*numbers;
	int		size;

	numbers = ft_strdup("0123456789abcdef");
	size = ft_itoa_base_count(nb, base);
	ret = malloc(sizeof(char) * size + 1);
	ret[size--] = '\0';
	while (size >= 0)
	{
		ret[size--] = numbers[nb % base];
		nb /= base;
	}
	free(numbers);
	return (ret);
}