/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:32:16 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/30 14:32:42 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SPACE 32
# define KEY_ALT 65513

# define MOVESPEED 0.1
# define RS 0.1

# define WIDTH 1920
# define HEIGHT 1080
# define COL_BUF 0.2
# define BG_PATH "assets/textures/bg.xpm"
# define S_PATH  "assets/textures/start.xpm"
# define S_HOVER_PATH "assets/textures/start_hover.xpm"
# define E_PATH  "assets/textures/exit.xpm"
# define E_HOVER_PATH "assets/textures/exit_hover.xpm"
# define DOOR_PATH "assets/textures/door.xpm"
# define NUM_FRAMES 7
# define F1 "assets/textures/menu/frame_1.xpm"
# define F2 "assets/textures/menu/frame_2.xpm"
# define F3 "assets/textures/menu/frame_3.xpm"
# define F4 "assets/textures/menu/frame_4.xpm"
# define F5 "assets/textures/menu/frame_5.xpm"
# define F6 "assets/textures/menu/frame_6.xpm"
# define F7 "assets/textures/menu/frame_7.xpm"

#endif