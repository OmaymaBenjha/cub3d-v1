/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziane <aziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 03:00:00 by aziane            #+#    #+#             */
/*   Updated: 2025/12/28 03:00:00 by aziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <math.h>
# include "mlx.h"

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

typedef struct s_gc_node
{
	void				*pt;
	struct s_gc_node	*next;
}	t_gc_node;

typedef enum e_co_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}	t_co_type;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	rgb;
}	t_color;

typedef struct s_textures
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	char	*path;
}	t_textures;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_config
{
	t_textures	no_tex;
	t_textures	so_tex;
	t_textures	we_tex;
	t_textures	ea_tex;
	t_color		f_color;
	t_color		c_color;
	int			f_has_been_set;
	int			c_has_been_set;
	int			all_done;
	t_co_type	type;
}	t_config;

typedef struct s_p
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_p;

typedef struct s_rect
{
	int	x;
	int	y;
	int	height;
	int	width;
}	t_rect;

typedef struct s_menu
{
	t_img	bg;
	t_img	btn_start;
	t_img	btn_start_hover;
	t_img	btn_exit;
	t_img	btn_exit_hover;
	t_rect	start_rect;
	t_rect	exit_rect;
	t_img	frames[NUM_FRAMES];
	int		frame_index;
	int		frame_counter;
	t_rect	anim_left_rect;
	t_rect	anim_right_rect;
}	t_menu;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	dist;
}	t_sprite;

typedef struct s_door
{
	int				x;
	int				y;
	int				state;
	struct s_door	*next;
}	t_door;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_textures	img_buffer;
	t_config	config;
	char		**map;
	size_t		map_width;
	size_t		map_height;
	int			map_started;
	int			map_ended;
	int			p_count;
	int			map_exist;
	t_p			p;
	t_img		tex_north;
	t_img		tex_south;
	t_img		tex_west;
	t_img		tex_east;
	t_img		tex_door;
	int			game_state;
	t_menu		menu;
	int			mouse_x;
	int			mouse_y;
	t_door		*doors;
	int			mouse_locked;
	t_sprite	*sprites;
	int			sprite_count;
	double		z_buffer[WIDTH];
}	t_game;

typedef struct s_wall
{
	double	tex_pos;
	int		color;
	int		tex_x;
	int		tex_y;
}	t_wall;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		hit_do;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

int				ft_strcmp(const char *s1, const char *s2);
void			free_split(char **arr);
char			*get_next_line(int fd);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(char *value);
size_t			ft_strlen(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_atoi(const char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strtrim_newline(char *s);
int				ft_isdigit(int c);

/* garbage collector */
char			*gc_strdup(char *str);
void			gc_add_pt(void *pt);
char			*gc_substr(char const *s, unsigned int start, size_t len);
void			gc_freed(void);
char			**gc_split(char const *s, char c);
char			*gc_strjoin(char const *s1, char const *s2);
void			*gc_mall(size_t size);

/* map checking and parsing */
int				pre_check(int ac, char **av);
int				main_trigger(char *map, t_game *game);
int				process_tex(char **tex_tokens, t_config *config,
					int *current_line_done, char *line);
int				process_fc(char **fc_tokens, t_config *config,
					int *current_line_done);
int				is_p_char(char c);
int				process_map(char *line, t_game *game);
int				check_map_closed(t_game *game);
int				is_map_char(char c);
void			get_p_cord(t_game *game);
void			make_map_rectangular(t_game *game);
int				is_empty(char *line);
int				ft_isspace(char c);
int				check_game_map_state(t_game *game);
void			initiate_game_struct(t_game *game);
int				validate_map_content(char **s_line, char *line);
char			*join_tokens(char **tokens);
int				not_valid_num(char **rgb);
t_color			get_representation(char **tokens, int *line);

/* game core */
void			init_game(t_game *game);
void			render_welcome_page(t_game *game);
int				key_handler(int keycode, t_game *game);
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
int				track_mouse_pos(int x, int y, t_game *game);

void			drawing_engin(t_ray *ray, t_game *game, int x);
void			my_mlx_pixel_put(t_textures *data, int x, int y, int color);
void			raycasting_engine(t_game *game);
unsigned int	get_tex_color(t_img *tex, int x, int y);
int				check_mouse_event_bound(t_game *game, t_rect rect);
int				track_mouse_click(int button, int x, int y, t_game *game);
int				handle_exit(t_game *game);
void			toggle_door(t_game *game);
void			get_coll_buffer(t_game *game, double new_x, double new_y,
					char op);
void			get_coll_buffer_side(t_game *game, double new_x, double new_y,
					char op);
void			add_sprite(t_game *game, int ix, int iy);
void			cast_sprites(t_game *game);

#endif