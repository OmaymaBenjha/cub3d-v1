/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 22:21:14 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 22:25:40 by oben-jha         ###   ########.fr       */
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

static void	wall_and_tex_starting_pos(t_ray *ray, t_game *game,
		t_img **current_tex, double *wallX)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0)
	{
		(*wallX) = game->p.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
		if (ray->ray_dir_x > 0)
			*current_tex = &game->tex_east;
		else
			*current_tex = &game->tex_west;
	}
	else
	{
		(*wallX) = game->p.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
		if (ray->ray_dir_y > 0)
			*current_tex = &game->tex_south;
		else
			*current_tex = &game->tex_north;
	}
	(*wallX) -= floor(*wallX);
}

static void	draw_wall_pix(t_wall *wall, double step, t_img *current_img)
{
	if (wall->tex_pos >= current_img->height)
		wall->tex_pos = 0;
	wall->tex_y = (int)wall->tex_pos % current_img->height;
	wall->tex_pos += step;
	wall->color = get_tex_color(current_img, wall->tex_x, wall->tex_y);
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
	wall.tex_x = (int)(wallx * (double)current_tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		wall.tex_x = current_tex->width - wall.tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		wall.tex_x = current_tex->width - wall.tex_x - 1;
	step = 1.0 * current_tex->height / ray->line_height;
	wall.tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = -1;
	while (++y < ray->draw_start)
		my_mlx_pixel_put(&game->img_buffer, x, y, game->config.c_color.rgb);
	while (++y < ray->draw_end)
	{
		draw_wall_pix(&wall, step, current_tex);
		my_mlx_pixel_put(&game->img_buffer, x, y, wall.color);
	}
	while (++y < HEIGHT)
		my_mlx_pixel_put(&game->img_buffer, x, y, game->config.f_color.rgb);
}
