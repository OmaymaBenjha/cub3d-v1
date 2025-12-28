/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayt <sayt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 02:00:00 by sayt              #+#    #+#             */
/*   Updated: 2025/12/28 02:00:00 by sayt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calc_sprite_dims(double transform_y, int screen_x,
	int *draw, int sprite_height)
{
	draw[0] = -sprite_height / 2 + HEIGHT / 2;
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = sprite_height / 2 + HEIGHT / 2;
	if (draw[1] >= HEIGHT)
		draw[1] = HEIGHT - 1;
	draw[2] = -sprite_height / 2 + screen_x;
	if (draw[2] < 0)
		draw[2] = 0;
	draw[3] = sprite_height / 2 + screen_x;
	if (draw[3] >= WIDTH)
		draw[3] = WIDTH - 1;
	(void)transform_y;
}

static void	draw_column(t_game *game, int stripe, int *draw, int tex_x)
{
	int				y;
	int				tex_y;
	unsigned int	color;
	t_img			*tex;
	int				h;

	tex = &game->menu.torch[game->menu.torch_frame];
	h = draw[1] - draw[0];
	y = draw[0];
	while (y < draw[1])
	{
		tex_y = (y - draw[0]) * tex->height / h;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = get_tex_color(tex, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0 && color != 0xFF000000)
			my_mlx_pixel_put(&game->img_buffer, stripe, y, color);
		y++;
	}
}

static void	draw_sprite_stripe(t_game *game, int stripe, int *draw,
	double transform_y)
{
	int		tex_x;
	t_img	*tex;
	int		w;

	(void)transform_y;
	tex = &game->menu.torch[game->menu.torch_frame];
	w = draw[3] - draw[2];
	tex_x = (int)((stripe - draw[2]) * tex->width / w);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	draw_column(game, stripe, draw, tex_x);
}

static void	calc_transform(t_game *game, t_sprite *sp, double *tf)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = sp->x - game->p.posX;
	sprite_y = sp->y - game->p.posY;
	inv_det = 1.0 / (game->p.planeX * game->p.dirY
			- game->p.dirX * game->p.planeY);
	tf[0] = inv_det * (game->p.dirY * sprite_x
			- game->p.dirX * sprite_y);
	tf[1] = inv_det * (-game->p.planeY * sprite_x
			+ game->p.planeX * sprite_y);
}

void	render_sprite(t_game *game, t_sprite *sp)
{
	double	tf[2];
	int		screen_x;
	int		sprite_h;
	int		draw[4];
	int		stripe;

	calc_transform(game, sp, tf);
	if (tf[1] <= 0)
		return ;
	screen_x = (int)((WIDTH / 2) * (1 + tf[0] / tf[1]));
	sprite_h = abs((int)(HEIGHT / tf[1] * 0.3));
	calc_sprite_dims(tf[1], screen_x, draw, sprite_h);
	stripe = draw[2];
	while (stripe < draw[3])
	{
		if (stripe >= 0 && stripe < WIDTH
			&& tf[1] < game->z_buffer[stripe])
			draw_sprite_stripe(game, stripe, draw, tf[1]);
		stripe++;
	}
}
