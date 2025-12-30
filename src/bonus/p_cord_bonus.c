/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cord_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziane <aziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:45:00 by aziane            #+#    #+#             */
/*   Updated: 2025/12/28 01:45:00 by aziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_p_cord_pos(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_pos(t_p *p, char c)
{
	if (c == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -0.99;
	}
	else if (c == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 0.99;
	}
	else if (c == 'W')
	{
		p->dir_x = -0.99;
		p->dir_y = 0;
	}
	else if (c == 'E')
	{
		p->dir_x = 0.99;
		p->dir_y = 0;
	}
}

static void	set_plane(t_p *p)
{
	if (p->dir_y < -0.9)
	{
		p->plane_x = .66;
		p->plane_y = 0;
	}
	else if (p->dir_y > 0.9)
	{
		p->plane_x = -.66;
		p->plane_y = 0;
	}
	else if (p->dir_x < -0.9)
	{
		p->plane_x = 0;
		p->plane_y = -.66;
	}
	else if (p->dir_x > 0.9)
	{
		p->plane_x = 0;
		p->plane_y = .66;
	}
}

static void	process_map_cell(t_game *game, int r, int c, int *found)
{
	t_p	tmp_p;

	if (game->map[r][c] == 'T')
	{
		add_sprite(game, c, r);
		game->map[r][c] = '0';
	}
	if (!(*found) && is_p_cord_pos(game->map[r][c]))
	{
		memset(&tmp_p, 0, sizeof(t_p));
		tmp_p.pos_x = (double)c + .5;
		tmp_p.pos_y = (double)r + .5;
		set_pos(&tmp_p, game->map[r][c]);
		set_plane(&tmp_p);
		game->map[r][c] = '0';
		game->p = tmp_p;
		*found = 1;
	}
}

void	get_p_cord(t_game *game)
{
	size_t	r;
	size_t	c;
	int		found;

	r = 0;
	found = 0;
	while (r < game->mh)
	{
		c = 0;
		while (c < ft_strlen(game->map[r]))
		{
			process_map_cell(game, (int)r, (int)c, &found);
			c++;
		}
		r++;
	}
}
