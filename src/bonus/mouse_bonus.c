/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziane <aziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 23:00:00 by aziane            #+#    #+#             */
/*   Updated: 2025/12/25 23:00:00 by aziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_p(t_game *game, double speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->p.dir_x;
	old_plane_x = game->p.plane_x;
	game->p.dir_x = game->p.dir_x * cos(speed)
		- game->p.dir_y * sin(speed);
	game->p.dir_y = old_dir_x * sin(speed)
		+ game->p.dir_y * cos(speed);
	game->p.plane_x = game->p.plane_x * cos(speed)
		- game->p.plane_y * sin(speed);
	game->p.plane_y = old_plane_x * sin(speed)
		+ game->p.plane_y * cos(speed);
}

int	mouse_rotate_bonus(int x, int y, t_game *game)
{
	int		center_x;
	double	rot_speed;

	(void)y;
	game->mouse_x = x;
	game->mouse_y = y;
	if (game->game_state != 1 || !game->mouse_locked)
		return (0);
	center_x = WIDTH / 2;
	if (x != center_x)
	{
		rot_speed = (x - center_x) * 0.0005;
		rotate_p(game, rot_speed);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center_x, HEIGHT / 2);
	}
	return (0);
}

int	track_mouse_click_bonus(int button, int x, int y, t_game *game)
{
	game->mouse_x = x;
	game->mouse_y = y;
	if (button == 1)
	{
		if (check_mouse_event_bound(game, game->menu.start_rect))
		{
			if (game->game_state == 0)
			{
				game->game_state = 1;
				mlx_mouse_move(game->mlx_ptr, game->win_ptr,
					WIDTH / 2, HEIGHT / 2);
			}
		}
		if (check_mouse_event_bound(game, game->menu.exit_rect))
		{
			if (game->game_state == 0)
				handle_exit(game);
		}
	}
	return (0);
}

void	init_menu_buttons(t_game *game)
{
	game->menu.start_rect.width = 500;
	game->menu.start_rect.height = 220;
	game->menu.exit_rect.width = 500;
	game->menu.exit_rect.height = 220;
	game->menu.start_rect.x = WIDTH / 2 - game->menu.start_rect.width - 40;
	game->menu.start_rect.y = HEIGHT / 2;
	game->menu.exit_rect.x = WIDTH / 2 + 40;
	game->menu.exit_rect.y = HEIGHT / 2;
}
