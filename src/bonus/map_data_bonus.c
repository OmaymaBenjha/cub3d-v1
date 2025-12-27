/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 23:17:13 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 01:06:31 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == 'D')
		return (1);
	return (0);
}

int	is_p_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	add_line(t_game *game, char *line)
{
	char	**new_map;
	size_t	i;

	i = 0;
	new_map = (char **)gc_mall(sizeof(char *) * (game->map_height + 2));
	if (!new_map)
		(perror("Error\nMalloc failed for map"), exit(EXIT_FAILURE));
	while (i < game->map_height)
	{
		new_map[i] = game->map[i];
		i++;
	}
	new_map[i] = gc_strdup(line);
	if (!new_map)
		(perror("Error\nMalloc failed for map line"), exit(EXIT_FAILURE));
	new_map[i + 1] = NULL;
	game->map = new_map;
	game->map_height++;
}

static int	validate_map_line(char *line, t_game *game)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!is_map_char(line[i]))
			return (printf("Error\nInvalid char in map: '%c'\n", line[i]), 0);
		if (is_p_char(line[i]))
		{
			game->p_count++;
			if (game->p_count > 1)
				return (printf("Error\nTwo MTF in the map.\n"), 0);
		}
		if (line[i] == '0' || is_p_char(line[i]))
		{
			if (i > 0 && line[i - 1] == ' ')
				return (printf("Error\nTwo MTF in the map\n"), 0);
			if (line[i + 1] == ' ')
				return (printf("Error\n'0' or P surrounded by spc.\n"), 0);
		}
		i++;
	}
	game->map_started = 1;
	return (1);
}

int	process_map(char *line, t_game *game)
{
	if (!validate_map_line(line, game))
		return (0);
	if (!game->map)
	{
		game->map = (char **)gc_mall(sizeof(char *) * 2);
		if (!game->map)
			(perror("Error\nMalloc failed for map"), exit(EXIT_FAILURE));
		game->map[0] = gc_strdup(line);
		if (!game->map[0])
			(perror("Error\nMalloc failed for map line"), exit(EXIT_FAILURE));
		game->map[1] = NULL;
		game->map_height = 1;
	}
	else
		add_line(game, line);
	if (ft_strlen(line) > game->map_width)
		game->map_width = ft_strlen(line);
	game->map_exist = 1;
	return (1);
}
