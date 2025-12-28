/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:26:15 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 00:26:15 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x + game->p.dir_x * MOVESPEED;
	new_y = game->p.pos_y + game->p.dir_y * MOVESPEED;
	get_coll_buffer(game, new_x, new_y, '+');
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x - game->p.dir_x * MOVESPEED;
	new_y = game->p.pos_y - game->p.dir_y * MOVESPEED;
	get_coll_buffer(game, new_x, new_y, '-');
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x - game->p.plane_x * MOVESPEED;
	new_y = game->p.pos_y - game->p.plane_y * MOVESPEED;
	get_coll_buffer(game, new_x, new_y, '-');
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x + game->p.plane_x * MOVESPEED;
	new_y = game->p.pos_y + game->p.plane_y * MOVESPEED;
	get_coll_buffer(game, new_x, new_y, '+');
}
