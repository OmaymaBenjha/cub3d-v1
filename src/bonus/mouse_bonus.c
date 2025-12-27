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

	old_dir_x = game->p.dirX;
	old_plane_x = game->p.planeX;
	game->p.dirX = game->p.dirX * cos(speed)
		- game->p.dirY * sin(speed);
	game->p.dirY = old_dir_x * sin(speed)
		+ game->p.dirY * cos(speed);
	game->p.planeX = game->p.planeX * cos(speed)
		- game->p.planeY * sin(speed);
	game->p.planeY = old_plane_x * sin(speed)
		+ game->p.planeY * cos(speed);
}

int	mouse_rotate_bonus(int x, int y, t_game *game)
{
	int		center_x;
	double	rot_speed;

	(void)y;
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
				mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIDTH / 2, HEIGHT / 2);
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
