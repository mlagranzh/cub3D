#include "../cub3d.h"

void	**free_2d_int(int **p, size_t size)
{
	size_t	i;

	if (p == NULL)
		return (p);
	i = 0;
	while (i < size)
	{
		free(p[i]);
		i++;
	}
	free(p);
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