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
	while (i < game->map_height)
	{
		len = ft_strlen(game->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

void	make_map_rectangular(t_game *game)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new_line;

	game->map_width = get_max_width(game);
	i = -1;
	while (++i < game->map_height)
	{
		len = ft_strlen(game->map[i]);
		if (len < game->map_width)
		{
			new_line = gc_mall(sizeof(char) * (game->map_width + 1));
			if (!new_line)
				exit(1);
			j = -1;
			while (++j < len)
				new_line[j] = game->map[i][j];
			while (++j < game->map_width)
				new_line[j] = ' ';
			new_line[j] = '\0';
			game->map[i] = new_line;
		}
	}
}
