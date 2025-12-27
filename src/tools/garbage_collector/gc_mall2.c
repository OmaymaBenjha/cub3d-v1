#include "cub3d.h"



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

	new_str = ft_strjoin(s1, s2);
	if (!new_str)
	{
		perror("substr failed!");
		exit(EXIT_FAILURE);
	}
	gc_add_pt(new_str);
	return (new_str);
}
char	**gc_split(char const *s, char c)
{
	char	**new_arr;
	int		i;

	if (!s)
		return (NULL);
	new_arr = ft_split(s, c);
	if (!new_arr)
	{
		perror("split failed!");
		exit(EXIT_FAILURE);
	}
	gc_add_pt(new_arr);
	i = 0;
	while (new_arr[i])
	{
		gc_add_pt(new_arr[i]);
		i++;
	}
	return (new_arr);
}