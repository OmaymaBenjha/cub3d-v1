/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student                                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 23:00:00 by student           #+#    #+#             */
/*   Updated: 2025/12/25 23:00:00 by student          ###   ########.fr       */
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
				mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
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
	int	btn_w;
	int	btn_h;

	btn_w = game->menu.btn_start.width / 3;
	btn_h = game->menu.btn_start.height / 3;
	game->menu.start_rect.x = (WIDTH / 2) - (btn_w / 2);
	game->menu.start_rect.y = (HEIGHT / 2) - btn_h;
	game->menu.start_rect.width = btn_w;
	game->menu.start_rect.height = btn_h;
	btn_w = game->menu.btn_exit.width / 3;
	btn_h = game->menu.btn_exit.height / 3;
	game->menu.exit_rect.x = (WIDTH / 2) - (btn_w / 2);
	game->menu.exit_rect.y = (HEIGHT / 2) + 20;
	game->menu.exit_rect.width = btn_w;
	game->menu.exit_rect.height = btn_h;
}
