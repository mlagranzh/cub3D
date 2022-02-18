/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:22:23 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/18 12:38:39 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"

void	calculation_distance(t_sprites *sprites, t_player *player)
{
	int	i;

	i = -1;
	while (++i < sprites->num)
	{
		sprites->distance[i] = (player->pos_x - sprites->coordinates[i].x)
			* (player->pos_x - sprites->coordinates[i].x)
			+ (player->pos_y - sprites->coordinates[i].y)
			* (player->pos_y - sprites->coordinates[i].y);
		sprites->iterator[i] = i;
	}
}

void	calculation_coller(t_sprites *sprites)
{
	sprites->coller++;
	if (sprites->coller >= sprites->coller_max)
		sprites->coller = sprites->coller_min;
}

int	calculation_general_parameters(t_all *all, t_sprites_param *param, int i)
{
	param->sprite_x = all->sprites.coordinates[i].x - all->player.pos_x;
	param->sprite_y = all->sprites.coordinates[i].y - all->player.pos_y;
	if (sprites_approach_action(all, param->sprite_x,
			param->sprite_y, i) == FALSE)
		return (FALSE);
	param->inv_det = 1.0 / (all->player.plane_x * all->player.dir_y
			- all->player.dir_x * all->player.plane_y);
	param->transform_x = param->inv_det * (all->player.dir_y * param->sprite_x
			- all->player.dir_x * param->sprite_y);
	param->transform_y = param->inv_det * (-all->player.plane_y
			* param->sprite_x + all->player.plane_x * param->sprite_y);
	param->sprite_screen_x = (int)((SCREEN_WIDTH / 2)
			* (1 + param->transform_x / param->transform_y));
	param->sprite_height = abs((int)(SCREEN_HEIGHT / param->transform_y));
	return (TRUE);
}

void	calculation_start_end(t_sprites_param *param)
{
	param->draw_start_y = -param->sprite_height / 2 + SCREEN_HEIGHT / 2;
	if (param->draw_start_y < 0)
		param->draw_start_y = 0;
	param->draw_end_y = param->sprite_height / 2 + SCREEN_HEIGHT / 2;
	if (param->draw_end_y >= SCREEN_HEIGHT)
		param->draw_end_y = SCREEN_HEIGHT - 1;
	param->sprite_width = abs((int)(SCREEN_HEIGHT / param->transform_y));
	param->draw_start_x = -param->sprite_width / 2 + param->sprite_screen_x;
	if (param->draw_start_x < 0)
		param->draw_start_x = 0;
	param->draw_end_x = param->sprite_width / 2 + param->sprite_screen_x;
	if (param->draw_end_x > SCREEN_WIDTH)
		param->draw_end_x = SCREEN_WIDTH;
}
