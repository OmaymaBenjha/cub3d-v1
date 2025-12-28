/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 22:20:17 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 01:06:31 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_textures *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	ray_dir_and_steps(t_ray *ray, t_game *g)
{
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (g->p.posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - g->p.posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (g->p.posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - g->p.posY) * ray->deltaDistY;
	}
}

void	detect_wall_hit(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (game->map[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
		else if (game->map[ray->mapY][ray->mapX] == 'D')
			ray->hit = 2;
	}
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
}

void	raycasting_engine(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		ray.cameraX = 2 * x / (double)WIDTH - 1;
		ray.rayDirX = game->p.dirX + game->p.planeX * ray.cameraX;
		ray.rayDirY = game->p.dirY + game->p.planeY * ray.cameraX;
		ray.mapX = (int)game->p.posX;
		ray.mapY = (int)game->p.posY;
		ray_dir_and_steps(&ray, game);
		detect_wall_hit(&ray, game);
		drawing_engin(&ray, game, x);
		game->z_buffer[x] = ray.perpWallDist;
		x++;
	}
	cast_sprites(game);
}
