/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziane <aziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 02:12:00 by aziane            #+#    #+#             */
/*   Updated: 2025/12/28 02:12:00 by aziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_menu_vars(t_game *game)
{
	game->menu.start_rect.width = 500;
	game->menu.start_rect.height = 220;
	game->menu.exit_rect.width = 500;
	game->menu.exit_rect.height = 220;
	game->menu.start_rect.x = WIDTH / 2 - game->menu.start_rect.width - 40;
	game->menu.start_rect.y = HEIGHT / 2;
	game->menu.exit_rect.x = WIDTH / 2 + 40;
	game->menu.exit_rect.y = HEIGHT / 2;
	game->menu.frame_index = 0;
	game->menu.frame_counter = 0;
	game->menu.anim_left_rect.width = 150 - 150 * 0.3;
	game->menu.anim_left_rect.height = 658 - 658 * 0.3;
	game->menu.anim_left_rect.x = WIDTH / 4;
	game->menu.anim_left_rect.y = HEIGHT / 10;
	game->menu.anim_right_rect.width = 150 - 150 * 0.3;
	game->menu.anim_right_rect.height = 658 - 658 * 0.3;
	game->menu.anim_right_rect.x = WIDTH - WIDTH / 4 - 70;
	game->menu.anim_right_rect.y = HEIGHT / 10;
}

void	initiate_game_struct(t_game *game)
{
	game->config.all_done = 0;
	game->map_started = 0;
	game->map = NULL;
	game->mw = 0;
	game->mh = 0;
	game->map_ended = 0;
	game->p_count = 0;
	game->config.c_has_been_set = 0;
	game->config.f_has_been_set = 0;
	game->map_exist = 0;
	game->game_state = 0;
	init_menu_vars(game);
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
