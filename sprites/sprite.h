/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:22:50 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/17 15:23:22 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "../cub3d.h"

typedef struct s_sprites_param
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		tex_x;
	int		tex_y;
	int		color;
}	t_sprites_param;

typedef struct s_sprites_on_map
{
	int	fact_sprites_num;
	int	if_there_are;
	int	i;
	int	j;
}	t_sprites_on_map;

void	calculation_distance(t_sprites *sprites, t_player *player);
void	calculation_start_end(t_sprites_param *param);
void	put_sprites_on_map(t_all *all, t_map *map);
void	calculation_coller(t_sprites *sprites);
int		calculation_general_parameters(t_all *all,
			t_sprites_param *param, int i);

#endif
