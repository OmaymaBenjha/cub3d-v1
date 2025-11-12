#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

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
} t_co_type;

typedef struct s_color
{
    int r;
    int g;
    int b;
    int rgb;
}   t_color;
typedef struct s_textures
{
    void    *img_ptr;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
    char    *path;
}   t_textures;
typedef struct s_config
{
    t_textures  no_tex;
    t_textures  so_tex;
    t_textures  we_tex;
    t_textures  ea_tex;
    t_color     f_color;
    t_color     c_color;
    int         all_done;
    t_co_type   type;
} t_config;
typedef struct s_game
{
    void        *mlx_ptr;
    void        *win_ptr;
    t_textures  img_buffer;
    t_config    config;
    char        **map;
    int         map_width;
    int         map_height;
    int         map_started;
} t_game;

void	*gc_mall(size_t size);
void	gc_add_pt(void *pt);
void	gc_freed(void);
int     ft_strcmp(const char *s1, const char *s2);
void    free_split(char **arr);
#endif