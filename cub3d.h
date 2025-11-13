#ifndef CUB3D_H
#define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#endif
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h> 
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


int     ft_strcmp(const char *s1, const char *s2);
void    free_split(char **arr);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int     ft_strcmp(const char *s1, const char *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *value);
size_t  ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int     ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
char    *ft_strtrim_newline(char *s);

// map checking and parsing --------------------------------
int     pre_check(int ac, char **av);
int     main_trigger(char *map, t_game *game);
int     process_tex(char **tex_tokens, t_config *config, int *current_line_done);
int process_fc(char **fc_tokens, t_config *config, int *current_line_done);

#endif