/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student                                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 23:00:00 by student           #+#    #+#             */
/*   Updated: 2025/12/25 23:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	render_frame(t_game *game)
{
	if (game->game_state == 0)
		render_welcome_page(game);
	else
		raycasting_engine(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->img_buffer.img_ptr, 0, 0);
	return (0);
}

static void	load_texture(t_game *game, t_img *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
		(printf("Error\nCould not load texture: %s\n", path), exit(1));
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
}

void	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		(printf("MLX couldn't connect to the system's graphics\n"), exit(1));
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!game->win_ptr)
		(printf("Window couldn't be created!\n"), exit(1));
	game->img_buffer.img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	if (!game->img_buffer.img_ptr)
		(printf("Image couldn't be created!\n"), exit(1));
	game->img_buffer.addr = mlx_get_data_addr(game->img_buffer.img_ptr,
			&game->img_buffer.bpp, &game->img_buffer.line_len,
			&game->img_buffer.endian);
	load_texture(game, &game->tex_north, game->config.no_tex.path);
	load_texture(game, &game->tex_south, game->config.so_tex.path);
	load_texture(game, &game->tex_west, game->config.we_tex.path);
	load_texture(game, &game->tex_east, game->config.ea_tex.path);
	load_texture(game, &game->menu.bg, BG_PATH);
	load_texture(game, &game->menu.btn_exit, E_PATH);
	load_texture(game, &game->menu.btn_start, S_PATH);
	load_texture(game, &game->tex_door, DOOR_PATH);
	mlx_loop_hook(game->mlx_ptr, render_frame, game);
	mlx_hook(game->win_ptr, 2, 1L << 0, key_handler, game);
	mlx_hook(game->win_ptr, 6, 1L << 6, mouse_rotate_bonus, game);
	mlx_hook(game->win_ptr, 4, 1L << 2, track_mouse_click_bonus, game);
	mlx_hook(game->win_ptr, 17, 0, handle_exit, game);
	mlx_loop(game->mlx_ptr);
}
