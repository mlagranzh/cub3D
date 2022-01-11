/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 15:41:43 by celys             #+#    #+#             */
/*   Updated: 2022/01/11 18:28:56 by celys            ###   ########.fr       */
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

char **ft_realloc(char **mas, char *new_line)
{
	char **new_mas;
	int mas_len;
	int i;

	if (!mas)
	{
		mas_len = 2;
		new_mas = (char **)malloc(sizeof(char *) * mas_len);
		new_mas[0] = new_line;
		new_mas[1] = NULL;
	}
	else
	{
		mas_len = 0;
		while (mas && mas[mas_len])
			mas_len++;
		mas_len++;
		new_mas = (char **)malloc(sizeof(char *) * (mas_len + 1));
		i = -1;
		while (++i < mas_len - 1)
			new_mas[i] = mas[i];
		new_mas[i] = new_line;
		new_mas[i + 1] = NULL;
		free (mas);
	}
	return (new_mas);
}
