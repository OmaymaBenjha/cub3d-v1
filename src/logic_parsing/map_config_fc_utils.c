/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config_fc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:52:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/26 15:52:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	get_representation(char **tokens, int *line)
{
	t_color	c;

	ft_memset(&c, 0, sizeof(t_color));
	if (!tokens[0] || !tokens[1] || !tokens[2])
	{
		*line = 0;
		return (printf("Error\nrgb item is missing.\n"), c);
	}
	c.r = ft_atoi(tokens[0]);
	c.g = ft_atoi(tokens[1]);
	c.b = ft_atoi(tokens[2]);
	if (c.r < 0 || c.r > 255 || c.g < 0 || c.g > 255 || c.b < 0 || c.b > 255)
	{
		*line = 0;
		return (printf("Error\nrgb is out of range.\n"), c);
	}
	c.rgb = (c.r << 16) | (c.g << 8) | c.b;
	return (c);
}

static int	is_valid_digit(char *s)
{
	int	j;

	j = 0;
	while (s[j])
	{
		if (!ft_isdigit(s[j]) && s[j] != ' ')
			return (0);
		if (j != 0 && ft_isdigit(s[j - 1]) && s[j] == ' ' && s[j + 1])
			return (0);
		j++;
	}
	return (1);
}

int	not_valid_num(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i] != NULL)
	{
		if (!is_valid_digit(rgb[i]))
			printf("Error\nInvalid rgb representation: %s\n", rgb[i]);
		return (0);
		i++;
	}
	return (1);
}

char	*join_tokens(char **tokens)
{
	char	*result;
	char	*tmp;
	int		i;

	if (!tokens || !tokens[0])
		return (NULL);
	result = gc_strdup(tokens[1]);
	if (!result)
		return (printf("Error\nstrdup failed.\n"), NULL);
	i = 2;
	while (tokens[i])
	{
		tmp = gc_strjoin(result, " ");
		if (!tmp)
			return (printf("Error\nstrjoin failed.\n"), NULL);
		result = gc_strjoin(tmp, tokens[i]);
		if (!result)
			return (printf("Error\nstrjoin failed.\n"), NULL);
		i++;
	}
	return (result);
}
