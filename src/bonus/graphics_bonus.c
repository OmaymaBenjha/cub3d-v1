/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 22:14:39 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/26 22:14:39 by oben-jha         ###   ########.fr       */
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

static void	mlx_hooks_calls(t_game *game)
{
	mlx_loop_hook(game->mlx_ptr, render_frame, game);
	mlx_hook(game->win_ptr, 2, 1L << 0, key_handler, game);
	mlx_hook(game->win_ptr, 4, 1L << 2, track_mouse_click_bonus, game);
	mlx_hook(game->win_ptr, 6, 1L << 6, mouse_rotate_bonus, game);
	mlx_hook(game->win_ptr, 17, 0, handle_exit, game);
}

static void	load_all_textures(t_game *game)
{
	load_texture(game, &game->tex_north, game->config.no_tex.path);
	load_texture(game, &game->tex_south, game->config.so_tex.path);
	load_texture(game, &game->tex_west, game->config.we_tex.path);
	load_texture(game, &game->tex_east, game->config.ea_tex.path);
	load_texture(game, &game->menu.bg, BG_PATH);
	load_texture(game, &game->menu.btn_exit, E_PATH);
	load_texture(game, &game->menu.btn_start, S_PATH);
	load_texture(game, &game->menu.btn_start_hover, S_HOVER_PATH);
	load_texture(game, &game->menu.btn_exit_hover, E_HOVER_PATH);
	load_texture(game, &game->tex_door, DOOR_PATH);
	load_texture(game, &game->menu.torch[0],
		"assets/textures/menu/torch_0.xpm");
	load_texture(game, &game->menu.torch[1],
		"assets/textures/menu/torch_1.xpm");
	load_texture(game, &game->menu.torch[2],
		"assets/textures/menu/torch_2.xpm");
	load_texture(game, &game->menu.torch[3],
		"assets/textures/menu/torch_3.xpm");
	load_texture(game, &game->menu.torch[4],
		"assets/textures/menu/torch_4.xpm");
	load_texture(game, &game->menu.torch[5],
		"assets/textures/menu/torch_5.xpm");
}

void	init_game(t_game *game)
{
	game->mouse_locked = 1;
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
	load_all_textures(game);
	init_menu_buttons(game);
	mlx_hooks_calls(game);
	mlx_loop(game->mlx_ptr);
}
