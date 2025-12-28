/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* ************************************************************************** */

#include "cub3d.h"

static void	sort_sprites(t_game *game)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < game->sprite_count)
	{
		game->sprites[i].dist = pow(game->p.posX - game->sprites[i].x, 2)
			+ pow(game->p.posY - game->sprites[i].y, 2);
		i++;
	}
	i = 0;
	while (i < game->sprite_count - 1)
	{
		j = i + 1;
		while (j < game->sprite_count)
		{
			if (game->sprites[j].dist > game->sprites[i].dist)
			{
				tmp = game->sprites[i];
				game->sprites[i] = game->sprites[j];
				game->sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

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

static void	draw_sprite_stripe(t_game *game, int stripe, int *draw,
	double transform_y)
{
	int				y;
	int				tex_x;
	int				tex_y;
	unsigned int	color;
	t_img			*tex;
	int				sprite_height;
	int				sprite_width;

	sprite_height = draw[1] - draw[0];
	sprite_width = draw[3] - draw[2];
	tex = &game->menu.torch[game->menu.torch_frame];
	tex_x = (int)((stripe - draw[2]) * tex->width / sprite_width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	y = draw[0];
	while (y < draw[1])
	{
		tex_y = (y - draw[0]) * tex->height / sprite_height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = get_tex_color(tex, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0 && color != 0xFF000000)
			my_mlx_pixel_put(&game->img_buffer, stripe, y, color);
		y++;
	}
	(void)transform_y;
}

static void	render_sprite(t_game *game, t_sprite *sp)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		sprite_height;
	int		draw[4];
	int		stripe;

	sprite_x = sp->x - game->p.posX;
	sprite_y = sp->y - game->p.posY;
	inv_det = 1.0 / (game->p.planeX * game->p.dirY
			- game->p.dirX * game->p.planeY);
	transform_x = inv_det * (game->p.dirY * sprite_x
			- game->p.dirX * sprite_y);
	transform_y = inv_det * (-game->p.planeY * sprite_x
			+ game->p.planeX * sprite_y);
	if (transform_y <= 0)
		return ;
	screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
	sprite_height = abs((int)(HEIGHT / transform_y * 0.3));
	calc_sprite_dims(transform_y, screen_x, draw, sprite_height);
	stripe = draw[2];
	while (stripe < draw[3])
	{
		if (stripe >= 0 && stripe < WIDTH
			&& transform_y < game->z_buffer[stripe])
			draw_sprite_stripe(game, stripe, draw, transform_y);
		stripe++;
	}
}

void	cast_sprites(t_game *game)
{
	int	i;

	if (game->sprite_count == 0)
		return ;
	game->menu.torch_counter++;
	if (game->menu.torch_counter >= 10)
	{
		game->menu.torch_counter = 0;
		game->menu.torch_frame = (game->menu.torch_frame + 1) % TORCH_FRAMES;
	}
	sort_sprites(game);
	i = 0;
	while (i < game->sprite_count)
	{
		render_sprite(game, &game->sprites[i]);
		i++;
	}
}
