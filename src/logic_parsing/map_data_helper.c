/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:26:49 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/22 12:26:49 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_column_edges(t_game *game)
{
	size_t	c;

	c = 0;
	while (c < game->map_width)
	{
		if (c < ft_strlen(game->map[0]) && (game->map[0][c] == '0'
			|| is_p_char(game->map[0][c])))
			return (printf("Error\nMap not closed (top edge).\n"), 0);
		if (c < ft_strlen(game->map[game->map_height - 1])
			&& (game->map[game->map_height - 1][c] == '0'
			|| is_p_char(game->map[game->map_height - 1][c])))
			return (printf("Error\nMap not closed (bottom edge).\n"), 0);
		c++;
	}
	return (1);
}

static int	check_neighbors(t_game *game, size_t r, size_t c)
{
	if (r == 0 || (c >= ft_strlen(game->map[r - 1])
			|| game->map[r - 1][c] == ' ' || game->map[r - 1][c] == '\0'))
		return (printf("Error\nMap open (top neighbor).\n"), 0);
	if (r == game->map_height - 1
		|| (c >= ft_strlen(game->map[r + 1])
			|| game->map[r + 1][c] == ' ' || game->map[r + 1][c] == '\0'))
		return (printf("Error\nMap open (bottom neighbor).\n"), 0);
	if (c == 0 || game->map[r][c - 1] == ' ')
		return (printf("Error\nMap open (left neighbor).\n"), 0);
	if (c == ft_strlen(game->map[r]) - 1 || game->map[r][c + 1] == ' ')
		return (printf("Error\nMap open (right neighbor).\n"), 0);
	return (1);
}

static int	check_neighbor_loop(t_game *game, size_t r)
{
	size_t	c;
	char	current_char;

	c = 0;
	while (c < ft_strlen(game->map[r]))
	{
		current_char = game->map[r][c];
		if (current_char == '0' || is_p_char(current_char))
		{
			if (!check_neighbors(game, r, c))
				return (0);
		}
		c++;
	}
	return (1);
}

static int	check_row_closure(t_game *game, size_t r)
{
	size_t	c;
	size_t	start;
	size_t	end;

	c = 0;
	start = (size_t) - 1;
	while (game->map[r][c])
	{
		if (game->map[r][c] != ' ' && start == (size_t) - 1)
			start = c;
		if (game->map[r][c] != ' ')
			end = c;
		c++;
	}
	if (start != (size_t) - 1 && (game->map[r][start] == '0'
		|| is_p_char(game->map[r][start])))
		return (printf("Error\nMap not closed (left edge).\n"), 0);
	if (end != (size_t) - 1 && (game->map[r][end] == '0'
		|| is_p_char(game->map[r][end])))
		return (printf("Error\nMap not closed (right edge).\n"), 0);
	return (1);
}

int	check_map_closed(t_game *game)
{
	size_t	r;

	if (!check_column_edges(game))
		return (0);
	r = 0;
	while (r < game->map_height)
	{
		if (!check_row_closure(game, r))
			return (0);
		if (!check_neighbor_loop(game, r))
			return (0);
		r++;
	}
	return (1);
}
