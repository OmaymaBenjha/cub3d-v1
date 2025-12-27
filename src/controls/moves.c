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

	new_x = game->p.posX + game->p.dirX * MOVESPEED;
	new_y = game->p.posY + game->p.dirY * MOVESPEED;
	get_coll_buffer(game, new_x, new_y, '+');
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.posX - game->p.dirX * MOVESPEED;
	new_y = game->p.posY - game->p.dirY * MOVESPEED;
	get_coll_buffer(game, new_x, new_y, '-');
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.posX - game->p.planeX * MOVESPEED;
	new_y = game->p.posY - game->p.planeY * MOVESPEED;
	get_coll_buffer(game, new_x, new_y, '-');
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.posX + game->p.planeX * MOVESPEED;
	new_y = game->p.posY + game->p.planeY * MOVESPEED;
	get_coll_buffer(game, new_x, new_y, '+');
}
