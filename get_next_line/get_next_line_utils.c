#include "get_next_line.h"

size_t	gnl_strlen (const char *str)
{
	size_t	k;

	k = 0;
	while (str[k] != '\0')
		k++;
	return (k);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	size_t			count_byte;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	if (gnl_strlen(s) < start)
		count_byte = 1;
	else if (gnl_strlen(s) - start >= len)
		count_byte = (len + 1) * sizeof(char);
	else
		count_byte = (gnl_strlen(s) - start + 1) * sizeof(char);
	p = malloc (count_byte);
	if (p == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0' && gnl_strlen(s) >= start)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

size_t	gnl_strchr(const char *s, int c)
{
	int	output;

	output = 0;
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		output++;
		if (*s == c)
			return (output);
		s++;
	}
	if (c == '\0')
		return (output);
	return (0);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	p = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (p == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		p[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		p[i] = *s2;
		s2++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*gnl_strdup(char *s)
{
	char	*p;
	size_t	len;
	size_t	i;

	i = 0;
	len = gnl_strlen(s);
	p = malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (i != len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
