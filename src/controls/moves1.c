/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:26:28 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 01:17:41 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_game *game)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->p.dirX;
	old_planex = game->p.planeX;
	game->p.dirX = game->p.dirX * cos(RS) - game->p.dirY * sin(RS);
	game->p.dirY = old_dirx * sin(RS) + game->p.dirY * cos(RS);
	game->p.planeX = game->p.planeX * cos(RS) - game->p.planeY * sin(RS);
	game->p.planeY = old_planex * sin(RS) + game->p.planeY * cos(RS);
}

void	rotate_left(t_game *game)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->p.dirX;
	old_planex = game->p.planeX;
	game->p.dirX = game->p.dirX * cos(-RS) - game->p.dirY * sin(-RS);
	game->p.dirY = old_dirx * sin(-RS) + game->p.dirY * cos(-RS);
	game->p.planeX = game->p.planeX * cos(-RS) - game->p.planeY * sin(-RS);
	game->p.planeY = old_planex * sin(-RS) + game->p.planeY * cos(-RS);
}

int	track_mouse_click(int button, int x, int y, t_game *game)
{
	game->mouse_x = x;
	game->mouse_y = y;
	if (button == 1)
	{
		if (check_mouse_event_bound(game, game->menu.start_rect))
		{
			if (game->game_state == 0)
				game->game_state = 1;
		}
	}
	else if (button == 1)
	{
		if (check_mouse_event_bound(game, game->menu.exit_rect))
		{
			if (game->game_state == 0)
				handle_exit(game);
		}
	}
	return (0);
}

int	track_mouse_pos(int x, int y, t_game *game)
{
	game->mouse_x = x;
	game->mouse_y = y;
	return (0);
}
