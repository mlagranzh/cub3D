/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:20:49 by celys             #+#    #+#             */
/*   Updated: 2022/02/18 13:38:21 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy(t_all *all)
{
	mlx_destroy(all);
	cub_free(all);
	exit(0);
	return (0);
}

int	key_press(int key, t_all *all)
{
	if (key == KEY_W || key == KEY_S)
		move_straight(key, all);
	if (key == KEY_A || key == KEY_D)
		move_side(key, all);
	if (key == KEY_LEFT)
		rotate(key, all, ROTATE_SPEED);
	if (key == KEY_RIGHT)
		rotate(key, all, ROTATE_SPEED);
	if (key == KEY_ESC)
		destroy(all);
	draw_screen(all);
	draw_sprites(all);
	draw_minimap(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (SUCCESS);
}
