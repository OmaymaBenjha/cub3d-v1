/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:21:09 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 00:21:09 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		move_forward(game);
	if (keycode == KEY_S)
		move_backward(game);
	if (keycode == KEY_LEFT)
		rotate_left(game);
	if (keycode == KEY_RIGHT)
		rotate_right(game);
	if (keycode == KEY_A)
		move_left(game);
	if (keycode == KEY_D)
		move_right(game);
}

#ifdef BONUS

static void	handle_mouse(t_game *game)
{
	game->mouse_locked = !game->mouse_locked;
	if (game->mouse_locked)
		mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	else
		mlx_mouse_show(game->mlx_ptr, game->win_ptr);
}

#else

static void	handle_mouse(t_game *game)
{
	(void)game;
}

#endif

int	key_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_exit(game);
	if (keycode == KEY_ALT)
		handle_mouse(game);
	if (keycode == KEY_SPACE)
		toggle_door(game);
	handle_movement(keycode, game);
	return (0);
}
