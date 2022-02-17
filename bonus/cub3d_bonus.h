/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:56:09 by celys             #+#    #+#             */
/*   Updated: 2022/02/17 15:41:10 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../mandatory/cub3d.h"

//screenshot
void			screenshot(t_all *all);
int				**create_color_map(t_data *img);
int				search_in_array(int *array, int search);
int				*add_to_dict(int *array, int number);
int				*create_dictionary(int **array);

//fog
void			fog(t_all *all);
int				fog_init(t_all *all);
#endif