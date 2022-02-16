/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 22:03:31 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/16 22:03:32 by ChelseyLeon      ###   ########.fr       */
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
