/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziane <aziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 02:00:00 by aziane            #+#    #+#             */
/*   Updated: 2025/12/28 02:00:00 by aziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calc_sprite_dims(int screen_x, int *params)
{
	params[0] = -params[5] / 2 + HEIGHT / 2;
	if (params[0] < 0)
		params[0] = 0;
	params[1] = params[5] / 2 + HEIGHT / 2;
	if (params[1] >= HEIGHT)
		params[1] = HEIGHT - 1;
	params[2] = -params[4] / 2 + screen_x;
	if (params[2] < 0)
		params[2] = 0;
	params[3] = params[4] / 2 + screen_x;
	if (params[3] >= WIDTH)
		params[3] = WIDTH - 1;
}

static void	draw_column(t_game *game, int stripe, int *params, int tex_x)
{
	int				y;
	int				tex_y;
	unsigned int	color;
	t_img			*tex;
	int				d;

	tex = &game->menu.frames[game->menu.frame_index];
	y = params[0];
	while (y < params[1])
	{
		d = y * 256 - HEIGHT * 128 + params[5] * 128;
		tex_y = ((d * tex->height) / params[5]) / 256;
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

static void	draw_sprite_stripe(t_game *game, int stripe, int *params, int sx)
{
	int		tex_x;
	t_img	*tex;

	tex = &game->menu.frames[game->menu.frame_index];
	tex_x = (256 * (stripe - (-params[4] / 2 + sx))
			* tex->width / params[4]) / 256;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	draw_column(game, stripe, params, tex_x);
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
	int		params[6];
	int		stripe;
	t_img	*tex;

	calc_transform(game, sp, tf);
	if (tf[1] <= 0)
		return ;
	tex = &game->menu.frames[game->menu.frame_index];
	screen_x = (int)((WIDTH / 2) * (1 + tf[0] / tf[1]));
	params[5] = abs((int)(HEIGHT / tf[1] * 0.8));
	params[4] = abs((int)(params[5] * ((double)tex->width / tex->height)));
	calc_sprite_dims(screen_x, params);
	stripe = params[2];
	while (stripe < params[3])
	{
		if (stripe >= 0 && stripe < WIDTH
			&& tf[1] < game->z_buffer[stripe])
			draw_sprite_stripe(game, stripe, params, screen_x);
		stripe++;
	}
}
