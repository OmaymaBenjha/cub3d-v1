/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_page.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayt <sayt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 03:00:00 by sayt              #+#    #+#             */
/*   Updated: 2025/12/28 03:00:00 by sayt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_btn_loop(t_game *game, t_img *img, t_rect *rect, double *sc)
{
	int				tex_x;
	int				tex_y;
	unsigned int	color;
	int				x;
	int				y;

	x = rect->x - 1;
	while (++x < (rect->x + rect->width))
	{
		y = rect->y - 1;
		while (++y < (rect->y + rect->height))
		{
			tex_x = (int)((x - rect->x) * sc[0]);
			tex_y = (int)((y - rect->y) * sc[1]);
			if (tex_x >= img->width)
				tex_x = img->width - 1;
			if (tex_y >= img->height)
				tex_y = img->height - 1;
			color = get_tex_color(img, tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(&game->img_buffer, x, y, color);
		}
	}
}

static void	draw_btn(t_game *game, t_img *img, t_rect *rect)
{
	double	sc[2];

	sc[0] = (double)img->width / rect->width;
	sc[1] = (double)img->height / rect->height;
	draw_btn_loop(game, img, rect, sc);
}

int	check_mouse_event_bound(t_game *game, t_rect rect)
{
	if (game->mouse_x >= rect.x
		&& game->mouse_x <= (rect.x + rect.width)
		&& game->mouse_y >= rect.y
		&& game->mouse_y <= (rect.y + rect.height))
		return (1);
	return (0);
}

static void	draw_background(t_game *game)
{
	int		x;
	int		y;
	int		tex_x;
	int		tex_y;
	double	sc[2];

	sc[0] = (double)game->menu.bg.width / WIDTH;
	sc[1] = (double)game->menu.bg.height / HEIGHT;
	x = 0;
	while (x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			tex_x = (int)(x * sc[0]);
			tex_y = (int)(y * sc[1]);
			if (tex_x >= game->menu.bg.width)
				tex_x = game->menu.bg.width - 1;
			if (tex_y >= game->menu.bg.height)
				tex_y = game->menu.bg.height - 1;
			my_mlx_pixel_put(&game->img_buffer, x, y,
				get_tex_color(&game->menu.bg, tex_x, tex_y));
		}
		x++;
	}
}

void	render_welcome_page(t_game *game)
{
	t_rect	draw_start;
	t_rect	draw_exit;
	t_img	*img_start;
	t_img	*img_exit;

	draw_background(game);
	draw_start = game->menu.start_rect;
	draw_exit = game->menu.exit_rect;
	img_start = &game->menu.btn_start;
	img_exit = &game->menu.btn_exit;
	if (check_mouse_event_bound(game, game->menu.start_rect))
		img_start = &game->menu.btn_start_hover;
	if (check_mouse_event_bound(game, game->menu.exit_rect))
		img_exit = &game->menu.btn_exit_hover;
	draw_btn(game, img_start, &draw_start);
	draw_btn(game, img_exit, &draw_exit);
}
