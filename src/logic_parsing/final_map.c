/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziane <aziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 21:53:57 by aziane            #+#    #+#             */
/*   Updated: 2025/12/27 21:53:57 by aziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	get_max_width(t_game *game)
{
	size_t	max;
	size_t	i;
	size_t	len;

	max = 0;
	i = 0;
	while (i < game->mh)
	{
		len = ft_strlen(game->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*pad_map_line(char *line, size_t mw)
{
	size_t	len;
	size_t	i;
	char	*new_line;

	len = ft_strlen(line);
	new_line = gc_mall(sizeof(char) * (mw + 1));
	if (!new_line)
		exit(1);
	i = 0;
	while (i < len)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < mw)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

void	make_map_rectangular(t_game *game)
{
	size_t	i;
	size_t	len;

	game->mw = get_max_width(game);
	i = 0;
	while (i < game->mh)
	{
		len = ft_strlen(game->map[i]);
		if (len < game->mw)
			game->map[i] = pad_map_line(game->map[i], game->mw);
		i++;
	}
}
