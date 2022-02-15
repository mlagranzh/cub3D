/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:51:35 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2022/02/15 17:52:39 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
