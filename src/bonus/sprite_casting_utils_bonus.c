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
	int *draw, int *dims)
{
	draw[0] = -dims[1] / 2 + HEIGHT / 2;
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = dims[1] / 2 + HEIGHT / 2;
	if (draw[1] >= HEIGHT)
		draw[1] = HEIGHT - 1;
	draw[2] = -dims[0] / 2 + screen_x;
	if (draw[2] < 0)
		draw[2] = 0;
	draw[3] = dims[0] / 2 + screen_x;
	if (draw[3] >= WIDTH)
		draw[3] = WIDTH - 1;
	(void)transform_y;
}

static void	draw_column(t_game *game, int stripe, int *draw, int *dims, int tex_x)
{
	int				y;
	int				tex_y;
	unsigned int	color;
	t_img			*tex;
	int				d;

	tex = &game->menu.frames[game->menu.frame_index];
	y = draw[0];
	while (y < draw[1])
	{
		d = (y) * 256 - HEIGHT * 128 + dims[1] * 128; // 256 and 128 factors to avoid floats
		tex_y = ((d * tex->height) / dims[1]) / 256;
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
	int *dims, int screen_x)
{
	int		tex_x;
	t_img	*tex;

	tex = &game->menu.frames[game->menu.frame_index];
	// Formula: (current_x - start_x) * tex_width / total_width
	// start_x is (screen_x - dims[0] / 2)
	tex_x = (int)(256 * (stripe - (-dims[0] / 2 + screen_x)) * tex->width / dims[0]) / 256;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	draw_column(game, stripe, draw, dims, tex_x);
}

static void	calc_transform(t_game *game, t_sprite *sp, double *tf)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = sp->x - game->p.pos_x;
	sprite_y = sp->y - game->p.pos_y;
	inv_det = 1.0 / (game->p.plane_x * game->p.dir_y
			- game->p.dir_x * game->p.plane_y);
	tf[0] = inv_det * (game->p.dir_y * sprite_x
			- game->p.dir_x * sprite_y);
	tf[1] = inv_det * (-game->p.plane_y * sprite_x
			+ game->p.plane_x * sprite_y);
}

void	render_sprite(t_game *game, t_sprite *sp)
{
	double	tf[2];
	int		screen_x;
	int		dims[2];
	int		draw[4];
	int		stripe;
	t_img	*tex;

	calc_transform(game, sp, tf);
	if (tf[1] <= 0)
		return ;
	tex = &game->menu.frames[game->menu.frame_index];
	screen_x = (int)((WIDTH / 2) * (1 + tf[0] / tf[1]));
	dims[1] = abs((int)(HEIGHT / tf[1] * 0.8));
	dims[0] = abs((int)(dims[1] * ((double)tex->width / tex->height)));
	calc_sprite_dims(tf[1], screen_x, draw, dims);
	stripe = draw[2];
	while (stripe < draw[3])
	{
		if (stripe >= 0 && stripe < WIDTH
			&& tf[1] < game->z_buffer[stripe])
			draw_sprite_stripe(game, stripe, draw, dims, screen_x);
		stripe++;
	}
}
