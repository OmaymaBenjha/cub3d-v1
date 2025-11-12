#include "cub3d.h"

char	*gc_itoa(int n)
{
	char	*new_str;

	new_str = ft_itoa(n);
	if (!new_str)
	{
		perror("substr failed!");
		exit(EXIT_FAILURE);
	}
	gc_add_pt(new_str);
	return (new_str);
}

void	*gc_mall(size_t size)
{
	void	*pt;

	pt = malloc(size);
	if (!pt)
	{
		perror("malloc failed!");
		exit(EXIT_FAILURE);
	}
	gc_add_pt(pt);
	return (pt);
}

char	*gc_strjoin(char const *s1, char const *s2)
{
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2);
	if (!new_str)
	{
		perror("substr failed!");
		exit(EXIT_FAILURE);
	}
	gc_add_pt(new_str);
	return (new_str);
}
