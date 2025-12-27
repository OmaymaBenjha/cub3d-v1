/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 21:53:51 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 21:53:51 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v');
}

int	is_empty(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	initiate_game_struct(t_game *game)
{
	game->config.all_done = 0;
	game->map_started = 0;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->map_ended = 0;
	game->p_count = 0;
	game->config.c_has_been_set = 0;
	game->config.f_has_been_set = 0;
	game->map_exist = 0;
	game->game_state = 0;
	game->menu.start_rect.width = 500;
	game->menu.start_rect.height = 220;
	game->menu.exit_rect.width = 500;
	game->menu.exit_rect.height = 220;
	game->menu.start_rect.x = WIDTH / 2 - game->menu.start_rect.width - 40;
	game->menu.start_rect.y = HEIGHT / 2;
	game->menu.exit_rect.x = WIDTH / 2 + 40;
	game->menu.exit_rect.y = HEIGHT / 2;
}

int	check_game_map_state(t_game *game)
{
	if (game->p_count == 0 && game->map_exist)
	{
		printf("Error\np starting position is missing in the map."
			"\nTry: S/N/W/E.\n");
		return (0);
	}
	if (game->config.all_done == 0 && !game->map_started)
	{
		printf("Map file cannot be empty!\n");
		return (0);
	}
	if (game->config.all_done < 6)
	{
		printf("Error\nMissing one or more config id.\n");
		return (0);
	}
	if (!game->map_started && !game->map_ended)
	{
		printf("Error\nMap data wasn't found in file\n");
		return (0);
	}
	if (!check_map_closed(game))
		return (0);
	return (1);
}

int	validate_map_content(char **s_line, char *line)
{
	char	*line_copy;

	line_copy = gc_strdup(line);
	if (!line_copy)
	{
		printf("Error\nstrdup failed!\n");
		return (0);
	}
	while (*line_copy)
	{
		if (!is_map_char(*line))
			break ;
		line_copy++;
	}
	if (is_map_char(*line))
	{
		printf("Error\nMap data found before or within the map config\n");
		return (0);
	}
	printf("Error\nInvalid texture identifier: %s\n", s_line[0]);
	return (0);
}
