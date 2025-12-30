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

int	key_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_exit(game);
	handle_extra_inputs(keycode, game);
	if (keycode == KEY_SPACE)
		toggle_door(game);
	handle_movement(keycode, game);
	return (0);
}
