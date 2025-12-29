/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   strings1.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aziane <aziane@student.42.fr>				  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/12/28 01:00:00 by aziane			  #+#	#+#			 */
/*   Updated: 2025/12/28 01:00:00 by aziane			 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static void	populate_split(char **arr, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			arr[j++] = ft_substr(s, start, i - start);
		}
		else
			i++;
	}
	arr[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	populate_split(arr, s, c);
	return (arr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s2)
		return (NULL);
	i = ft_strlen(s2);
	if (s1)
		i += ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i])
			str[i] = s1[i];
	else
		i = 0;
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = 0;
	return (str);
}
