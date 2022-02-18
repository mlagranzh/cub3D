/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_approach_action.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:35:51 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/18 12:35:54 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	sprites_approach_action(t_all *all, double x, double y, int i)
{
	(void)all;
	i = 0;
	if (fabs(x) < 0.2 && fabs(y) < 0.2)
		return (FALSE);
	return (TRUE);
}
