/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 21:42:25 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 22:19:34 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_tex_color(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

static void	get_current_tx(t_game *game, t_ray *ray, double *wallX,
		t_img **tx)
{
	if (ray->side == 0)
	{
		*wallX = game->p.posY + ray->perpWallDist * ray->rayDirY;
		if (ray->rayDirX > 0)
			*tx = &game->tex_east;
		else
			*tx = &game->tex_west;
	}
	else
	{
		*wallX = game->p.posX + ray->perpWallDist * ray->rayDirX;
		if (ray->rayDirY > 0)
			*tx = &game->tex_south;
		else
			*tx = &game->tex_north;
	}
}

static void	wall_and_tex_starting_pos(t_ray *ray, t_game *game,
		t_img **current_tex, double *wallX)
{
	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
	if (ray->hit == 2)
	{
		*current_tex = &game->tex_door;
		if (ray->side == 0)
			*wallX = game->p.posY + ray->perpWallDist * ray->rayDirY;
		else
			*wallX = game->p.posX + ray->perpWallDist * ray->rayDirX;
	}
	else
		get_current_tx(game, ray, wallX, current_tex);
	(*wallX) -= floor(*wallX);
}

static void	draw_wall_pix(t_wall *wall, double step, t_img *current_img)
{
	if (wall->texPos >= current_img->height)
		wall->texPos = 0;
	wall->texY = (int)wall->texPos % current_img->height;
	wall->texPos += step;
	wall->color = get_tex_color(current_img, wall->texX, wall->texY);
}

void	drawing_engin(t_ray *ray, t_game *game, int x)
{
	int		y;
	t_img	*current_tex;
	double	wallx;
	double	step;
	t_wall	wall;

	current_tex = NULL;
	wall_and_tex_starting_pos(ray, game, &current_tex, &wallx);
	wall.texX = (int)(wallx * (double)current_tex->width);
	if (ray->side == 0 && ray->rayDirX > 0)
		wall.texX = current_tex->width - wall.texX - 1;
	if (ray->side == 1 && ray->rayDirY < 0)
		wall.texX = current_tex->width - wall.texX - 1;
	step = 1.0 * current_tex->height / ray->lineHeight;
	wall.texPos = (ray->drawStart - HEIGHT / 2 + ray->lineHeight / 2) * step;
	y = -1;
	while (++y < ray->drawStart)
		my_mlx_pixel_put(&game->img_buffer, x, y, game->config.c_color.rgb);
	while (++y < ray->drawEnd)
	{
		draw_wall_pix(&wall, step, current_tex);
		my_mlx_pixel_put(&game->img_buffer, x, y, wall.color);
	}
	while (++y < HEIGHT)
		my_mlx_pixel_put(&game->img_buffer, x, y, game->config.f_color.rgb);
}
