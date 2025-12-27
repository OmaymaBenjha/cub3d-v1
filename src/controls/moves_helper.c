/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:22:22 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 06:30:33 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

void	get_coll_buffer(t_game *game, double new_x, double new_y,
		char op)
{
	double	bx;
	double	by;

	if (op == '-')
	{
		if (game->p.dirX < 0)
			bx = new_x + COL_BUF;
		else
			bx = new_x - COL_BUF;
		if (game->p.dirY < 0)
			by = new_y + COL_BUF;
		else
			by = new_y - COL_BUF;
	}
	else if (op == '+')
	{
		bx = new_x + (game->p.dirX > 0 ? COL_BUF : -COL_BUF);
    	by = new_y + (game->p.dirY > 0 ? COL_BUF : -COL_BUF);
	}
	if (game->map[(int)game->p.posY][(int)bx] != '1' && 
        game->map[(int)game->p.posY][(int)bx] != 'D')
        game->p.posX = new_x;
    if (game->map[(int)by][(int)game->p.posX] != '1' && 
        game->map[(int)by][(int)game->p.posX] != 'D')
        game->p.posY = new_y;
}

static t_door *find_door(t_door *list, int x, int y)
{
    while (list)
    {
        if (list->x == x && list->y == y)
            return (list);
        list = list->next;
    }
    return (NULL);
}

static void add_door_node(t_game *game, t_door d_node)
{
    t_door *new_node;

    new_node = gc_mall(sizeof(t_door));
    new_node->x = d_node.x;
    new_node->y = d_node.y;
    new_node->state = d_node.state;
    new_node->next = game->doors;
    game->doors = new_node;
}

void	toggle_door(t_game *game)
{
	int	tx;
	int	ty;
	t_door d_node;
    t_door *existing_node;

	tx = (int)(game->p.posX + game->p.dirX * 1.04);
	ty = (int)(game->p.posY + game->p.dirY * 1.04);
	if (game->map[ty][tx] == 'D' || game->map[ty][tx] == 'O')
	{
        existing_node = find_door(game->doors, tx, ty);
		if (!existing_node)
		{
            d_node.x = tx;
            d_node.y = ty;
            d_node.state = 1; 
			add_door_node(game, d_node);
			game->map[ty][tx] = 'O';
		}
		else
		{
			if (existing_node->state == 0)
			{
				game->map[ty][tx] = 'O';
				existing_node->state = 1;
			}
			else
			{
				game->map[ty][tx] = 'D';
				existing_node->state = 0;
			}	
		}	
	}
}
