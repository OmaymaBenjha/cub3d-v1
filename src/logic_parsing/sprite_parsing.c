/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayt <sayt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 02:15:00 by sayt              #+#    #+#             */
/*   Updated: 2025/12/28 02:15:00 by sayt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	snap_to_wall(t_game *game, t_sprite *sp, int ix, int iy)
{
	sp->x = (double)ix + 0.5;
	sp->y = (double)iy + 0.5;
	if (iy > 0 && game->map[iy - 1][ix] == '1')
		sp->y = (double)iy + 0.15;
	else if ((size_t)(iy + 1) < game->map_height
		&& game->map[iy + 1][ix] == '1')
		sp->y = (double)iy + 0.85;
	else if ((size_t)(ix + 1) < game->map_width
		&& game->map[iy][ix + 1] == '1')
		sp->x = (double)ix + 0.85;
	else if (ix > 0 && game->map[iy][ix - 1] == '1')
		sp->x = (double)ix + 0.15;
}

void	add_sprite(t_game *game, int ix, int iy)
{
	t_sprite	*new_arr;
	int			i;

	new_arr = gc_mall(sizeof(t_sprite) * (game->sprite_count + 1));
	if (!new_arr)
		(perror("Error\nMalloc failed for sprites"), exit(EXIT_FAILURE));
	i = 0;
	while (i < game->sprite_count)
	{
		new_arr[i] = game->sprites[i];
		i++;
	}
	snap_to_wall(game, &new_arr[i], ix, iy);
	new_arr[i].dist = 0;
	game->sprites = new_arr;
	game->sprite_count++;
}
