/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:51:35 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/16 04:54:30 by celys            ###   ########.fr       */
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

void	ft_change_sumbols_in_str(char *change_str, char *change_sumbols,
									char replacement_char)
{
	int	i;

	i = 0;
	while (change_str && *change_str)
	{
		while (change_sumbols[i] != '\0')
		{
			if (change_sumbols[i] == *change_str)
				*change_str = replacement_char;
			i++;
		}
		change_str++;
	}
}

void	replace(double *x, double x_new, double *y, double y_new)
{
	*x = x_new;
	*y = y_new;
}
