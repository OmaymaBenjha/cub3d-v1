/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayt <sayt@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 03:15:00 by sayt              #+#    #+#             */
/*   Updated: 2025/12/28 03:15:00 by sayt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_textures(t_game *game)
{
	int	i;

	if (game->img_buffer.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_buffer.img_ptr);
	if (game->tex_east.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->tex_east.img_ptr);
	if (game->tex_west.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->tex_west.img_ptr);
	if (game->tex_north.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->tex_north.img_ptr);
	if (game->tex_south.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->tex_south.img_ptr);
	if (game->tex_door.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->tex_door.img_ptr);
	i = -1;
	while (++i < TORCH_FRAMES)
		if (game->menu.torch[i].img_ptr)
			mlx_destroy_image(game->mlx_ptr, game->menu.torch[i].img_ptr);
}

static void	destroy_menu(t_game *game)
{
	if (game->menu.bg.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->menu.bg.img_ptr);
	if (game->menu.btn_exit.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->menu.btn_exit.img_ptr);
	if (game->menu.btn_start.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->menu.btn_start.img_ptr);
}

int	handle_exit(t_game *game)
{
	destroy_textures(game);
	destroy_menu(game);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	gc_freed();
	exit(0);
	return (0);
}
