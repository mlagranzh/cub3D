#include "../cub3d.h"

int	free_2d_int(int **p, size_t size)
{
	size_t	i;

	if (p == NULL)
		return (ERROR);
	i = 0;
	while (i < size)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (SUCCESS);
}

int	free_2d_char(char **p)
{
	size_t	i;

	if (p == NULL)
		return (ERROR);
	i = 0;
	while (p[i] != NULL)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (SUCCESS);
}

char	*my_strjoin(char *s1, char *s2, char *s3)
{
    char	*p;
    char	*tmp;
	
	tmp = ft_strjoin(s1, s2);
	p = ft_strjoin(tmp, s3);
	free(tmp);
	return (p);
}	