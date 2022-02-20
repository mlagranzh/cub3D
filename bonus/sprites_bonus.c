/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:32:11 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/18 15:21:00 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	light_on_off(t_all *all)
{
	if (all->sprites.coller_min == 0)
	{
		all->sprites.coller_min = all->sprites.coller_max;
		all->sprites.coller = all->sprites.coller_max;
		all->sprites.coller_mod = 30;
	}
	else
	{
		all->sprites.coller_min = 0;
		all->sprites.coller = 0;
		all->sprites.coller_mod = 45;
	}
}

int	sprites_approach_action(t_all *all, double x, double y, int i)
{
	if (fabs(x) < 0.2 && fabs(y) < 0.2)
	{
		if (all->sprites.coordinates[i].texture_name == BARREL)
			all->sprites.coordinates[i].texture_flag = 1;
		return (FALSE);
	}
	return (TRUE);
}

void	sprites_init_coller(t_all *all)
{
	all->sprites.coller = 0;
	all->sprites.coller_max = 89;
	all->sprites.coller_min = 0;
	all->sprites.coller_mod = 45;
}
