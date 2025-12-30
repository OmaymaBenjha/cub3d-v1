/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:22:48 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/30 14:22:48 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_mp_pixel(t_game *g, int x, int y, int mp_size)
{
	int	mx;
	int	my;

	mx = (int)g->p.pos_x + ((x - mp_size / 2.0) / MINI_TILE);
	my = (int)g->p.pos_y + ((y - mp_size / 2.0) / MINI_TILE);
	if (mx < 0 || my < 0 || my >= (int)g-> mh || mx >= (int)g->mw)
		my_mlx_pixel_put(&g->img_buffer, x + 30, y + 30, COLOR_VOID);
	else if (g->map[my][mx] == '1')
		my_mlx_pixel_put(&g->img_buffer, x + 30, y + 30, COLOR_WALL);
	else if (g->map[my][mx] == 'D' || g->map[my][mx] == 'O')
		my_mlx_pixel_put(&g->img_buffer, x + 30, y + 30, COLOR_DOOR);
	else if (g->map[my][mx] == '0')
		my_mlx_pixel_put(&g->img_buffer, x + 30, y + 30, COLOR_FLOOR);
	else
		my_mlx_pixel_put(&g->img_buffer, x + 30, y + 30, COLOR_VOID);
}

static void	draw_mp(t_game *g)
{
	int	x;
	int	y;
	int	mp_size;

	mp_size = WIDTH / 10;
	y = -1;
	while (y++ < mp_size)
	{
		x = -1;
		while (x++ < mp_size)
			draw_mp_pixel(g, x, y, mp_size);
	}
}

static void	draw_p(t_game *g)
{
	int	cx;
	int	cy;
	int	i;
	int	j;

	cx = ((WIDTH / 10) / 2) + 35;
	cy = ((WIDTH / 10) / 2) + 35;
	i = -3;
	while (i <= 3)
	{
		j = -3;
		while (j <= 3)
		{
			my_mlx_pixel_put(&g->img_buffer, cx + i, cy + j, COLOR_PLAYER);
			j++;
		}
		i++;
	}
}

static void	draw_pd(t_game *g)
{
	int		i;
	double	x;
	double	y;

	i = 0;
	while (i < 15)
	{
		x = ((WIDTH / 10) / 2) + 35 + g->p.dir_x * i;
		y = ((WIDTH / 10) / 2) + 35 + g->p.dir_y * i;
		my_mlx_pixel_put(&g->img_buffer, (int)x, (int)y, COLOR_DIR);
		i++;
	}
}

void	render_minimap(t_game *g)
{
	draw_mp(g);
	draw_p(g);
	draw_pd(g);
}
