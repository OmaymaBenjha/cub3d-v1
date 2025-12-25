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

static void	rotate_player(t_game *game, double speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dirX;
	old_plane_x = game->player.planeX;
	game->player.dirX = game->player.dirX * cos(speed)
		- game->player.dirY * sin(speed);
	game->player.dirY = old_dir_x * sin(speed)
		+ game->player.dirY * cos(speed);
	game->player.planeX = game->player.planeX * cos(speed)
		- game->player.planeY * sin(speed);
	game->player.planeY = old_plane_x * sin(speed)
		+ game->player.planeY * cos(speed);
}

int	mouse_rotate_bonus(int x, int y, t_game *game)
{
	int		center_x;
	double	rot_speed;

	(void)y;
	if (game->game_state != 1)
		return (0);
	center_x = WIDTH / 2;
	if (x != center_x)
	{
		rot_speed = (x - center_x) * 0.0005;
		rotate_player(game, rot_speed);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center_x, HEIGHT / 2);
	}
	return (0);
}
