/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziane <aziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 23:00:00 by aziane            #+#    #+#             */
/*   Updated: 2025/12/25 23:00:00 by aziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"
# define MINI_W 150
# define MINI_H 150
# define MINI_TILE 10

# define COLOR_WALL 0x00FFFFFF
# define COLOR_DOOR 0xF2C668

# define COLOR_FLOOR 0x00777777
# define COLOR_VOID 0x00000000
# define COLOR_PLAYER 0x00FF0000
# define COLOR_DIR 0x0000FF00

int		mouse_rotate_bonus(int x, int y, t_game *game);
int		track_mouse_click_bonus(int button, int x, int y, t_game *game);
void	init_menu_buttons(t_game *game);
void	toggle_door(t_game *game);
void	sort_sprites(t_game *game);
void	render_sprite(t_game *game, t_sprite *sp);
void	render_minimap(t_game *g);

#endif
