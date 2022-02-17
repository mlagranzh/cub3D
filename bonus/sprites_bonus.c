/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:32:11 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/17 15:32:17 by ChelseyLeon      ###   ########.fr       */
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
