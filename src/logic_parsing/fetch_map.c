/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziane <aziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 21:53:54 by aziane            #+#    #+#             */
/*   Updated: 2025/12/27 21:53:54 by aziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_config_line(char **s_line, t_game *game, char *line)
{
	int		current_line_done;

	current_line_done = 0;
	if (ft_strcmp(s_line[0], "NO") == 0 || ft_strcmp(s_line[0], "SO") == 0
		|| ft_strcmp(s_line[0], "EA") == 0 || ft_strcmp(s_line[0], "WE") == 0)
	{
		if (!process_tex(s_line, &game->config, &current_line_done, line))
			return (0);
	}
	else if (ft_strcmp(s_line[0], "F") == 0 || ft_strcmp(s_line[0], "C") == 0)
	{
		if (!process_fc(s_line, &game->config, &current_line_done))
			return (0);
	}
	else if (game->config.all_done < 6)
	{
		if (!validate_map_content(s_line, line))
			return (0);
	}
	else if (!process_map(line, game))
		return (0);
	if (current_line_done)
		game->config.all_done++;
	return (1);
}

static int	handle_empty_line(t_game *game)
{
	if (!game->map_started)
		return (1);
	else if (game->map_started && !game->map_ended)
	{
		game->map_started = 0;
		game->map_ended = 1;
		return (1);
	}
	return (1);
}

static int	parse_line(char *line, t_game *game)
{
	char	**tokens;

	if (is_empty(line))
		return (handle_empty_line(game));
	else if (game->map_ended)
	{
		printf("Error\nfound an empty line inside map data.\n");
		return (0);
	}
	tokens = gc_split(line, ' ');
	if (!tokens)
	{
		printf("Error\nft_split failed\n");
		return (0);
	}
	if (!process_config_line(tokens, game, line))
		return (0);
	return (1);
}

static int	read_map_loop(int fd, t_game *game)
{
	char	*line;
	char	*trimed_line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		trimed_line = ft_strtrim_newline(line);
		if (!trimed_line)
			return (printf("ERROR\nstriming line failed!\n"), free(line), 0);
		if (!parse_line(trimed_line, game))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	main_trigger(char *map, t_game *game)
{
	int		fd;

	initiate_game_struct(game);
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		perror("ERROR\nopen");
		exit(EXIT_FAILURE);
	}
	if (!read_map_loop(fd, game))
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (!check_game_map_state(game))
		return (0);
	return (1);
}
