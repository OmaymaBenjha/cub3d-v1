/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:26:28 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 22:53:52 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_game *game)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->p.dir_x;
	old_planex = game->p.plane_x;
	game->p.dir_x = game->p.dir_x * cos(RS) - game->p.dir_y * sin(RS);
	game->p.dir_y = old_dirx * sin(RS) + game->p.dir_y * cos(RS);
	game->p.plane_x = game->p.plane_x * cos(RS) - game->p.plane_y * sin(RS);
	game->p.plane_y = old_planex * sin(RS) + game->p.plane_y * cos(RS);
}

void	rotate_left(t_game *game)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->p.dir_x;
	old_planex = game->p.plane_x;
	game->p.dir_x = game->p.dir_x * cos(-RS) - game->p.dir_y * sin(-RS);
	game->p.dir_y = old_dirx * sin(-RS) + game->p.dir_y * cos(-RS);
	game->p.plane_x = game->p.plane_x * cos(-RS) - game->p.plane_y * sin(-RS);
	game->p.plane_y = old_planex * sin(-RS) + game->p.plane_y * cos(-RS);
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
