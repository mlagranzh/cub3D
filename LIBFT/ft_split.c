/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:43:36 by celys             #+#    #+#             */
/*   Updated: 2021/11/20 03:10:48 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_free(char **p)
{
	unsigned int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

static unsigned int	ft_count_array(char const *s, char c)
{
	unsigned int		i;
	unsigned int		count_array;

	if (!s)
		return (0);
	i = 0;
	count_array = 1;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] == c && s[i] != '\0')
				i++;
			count_array += 1;
		}
		i++;
	}
	return (count_array);
}

static	char	*ft_get_next_array(char *p, char const *s, char c)
{
	unsigned int		end;

	end = 0;
	while (*(s) != c && *(s) != '\0')
	{
		s++;
		end++;
	}
	p = (char *) ft_substr(s - end, 0, end);
	if (p == NULL)
		return (NULL);
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char			**p;
	unsigned int	i;
	unsigned int	len;

	if (!s)
		return (NULL);
	i = 0;
	p = (char **) ft_calloc((ft_count_array(s, c) + 1), sizeof(char *));
	if (p == NULL)
		return (NULL);
	len = ft_count_array(s, c);
	while (*s != '\0')
	{
		if (*s != c && i != len)
		{
			p[i] = ft_get_next_array(p[i], s, c);
			if (p[i] == NULL)
				return (ft_malloc_free(p));
			while (*(s) != c && *(s) != '\0')
				s++;
			i++;
		}
		s++;
	}
	return (p);
}
