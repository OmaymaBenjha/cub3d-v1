/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 22:13:21 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 22:18:35 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_door	*find_door(t_door *list, int x, int y)
{
	while (list)
	{
		if (list->x == x && list->y == y)
			return (list);
		list = list->next;
	}
	return (NULL);
}

static void	add_door_node(t_game *game, t_door d_node)
{
	t_door	*new_node;

	new_node = gc_mall(sizeof(t_door));
	new_node->x = d_node.x;
	new_node->y = d_node.y;
	new_node->state = d_node.state;
	new_node->next = game->doors;
	game->doors = new_node;
}

static void	handle_door_state(t_game *game, int x, int y)
{
	t_door	*node;
	t_door	new_d;

	node = find_door(game->doors, x, y);
	if (!node)
	{
		new_d.x = x;
		new_d.y = y;
		new_d.state = 1;
		add_door_node(game, new_d);
		game->map[y][x] = 'O';
	}
	else
	{
		if (node->state == 0)
		{
			game->map[y][x] = 'O';
			node->state = 1;
		}
		else
		{
			game->map[y][x] = 'D';
			node->state = 0;
		}
	}
}

void	toggle_door(t_game *game)
{
	int	tx;
	int	ty;

	tx = (int)(game->p.pos_x + game->p.dir_x * 1.04);
	ty = (int)(game->p.pos_y + game->p.dir_y * 1.04);
	if (game->map[ty][tx] == 'D' || game->map[ty][tx] == 'O')
		handle_door_state(game, tx, ty);
}
