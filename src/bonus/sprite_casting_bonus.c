/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziane <aziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:50:00 by aziane            #+#    #+#             */
/*   Updated: 2025/12/28 01:50:00 by aziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cast_sprites(t_game *game)
{
	int	i;

	if (game->sprite_count == 0)
		return ;
	game->menu.frame_counter++;
	if (game->menu.frame_counter >= 10)
	{
		game->menu.frame_counter = 0;
		game->menu.frame_index = (game->menu.frame_index + 1)
			% NUM_FRAMES;
	}
	sort_sprites(game);
	i = 0;
	while (i < game->sprite_count)
	{
		render_sprite(game, &game->sprites[i]);
		i++;
	}
}
