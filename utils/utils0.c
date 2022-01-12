/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 15:41:43 by celys             #+#    #+#             */
/*   Updated: 2022/01/12 20:23:55 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void printf_array(char **arr)
{
	int i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
}

char *delete_space_line(char *line)
{
	char *new_line = malloc(sizeof(char) * (ft_strlen(line)/2 + 1));
	
	int i = -1;
	while (*line)
	{
		if (*line != ' ')
			new_line[++i] = *line;
		line++;
	}
	new_line[++i] = '\0';
	
	return (new_line);
}

int		print_return(int retval, char *print_message)
{
	printf("%s\n", print_message);
	return (retval);
}

void	ft_change_sumbols_in_str(char *change_str, char *change_sumbols, char replacement_char)
{
	int i;

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