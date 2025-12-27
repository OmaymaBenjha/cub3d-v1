/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:22:22 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 22:13:13 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

static double	get_axis_offset(double dir, char op)
{
	if (op == '-')
	{
		if (dir < 0)
			return (COL_BUF);
		return (-COL_BUF);
	}
	if (dir < 0)
		return (-COL_BUF);
	return (COL_BUF);
}

void	get_coll_buffer(t_game *game, double new_x, double new_y, char op)
{
	double	bx;
	double	by;

	bx = new_x + get_axis_offset(game->p.dirX, op);
	by = new_y + get_axis_offset(game->p.dirY, op);
	if (game->map[(int)game->p.posY][(int)bx] != '1' &&
		game->map[(int)game->p.posY][(int)bx] != 'D')
	{
		game->p.posX = new_x;
	}
	if (game->map[(int)by][(int)game->p.posX] != '1' &&
		game->map[(int)by][(int)game->p.posX] != 'D')
	{
		game->p.posY = new_y;
	}
}
