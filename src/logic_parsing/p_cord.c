#include "cub3d.h"

static  int is_p_cord(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
static void set_pos(t_p *p, char c)
{
    if (c == 'N')
    {
        p->dirX = 0;
        p->dirY = -0.99;
    }
    else if (c == 'S')
    {
        p->dirX = 0;
        p->dirY = 0.99;
    }
    else if (c == 'W')
    {
        p->dirX = -0.99;
        p->dirY = 0;
    }
    else if (c == 'E')
    {
        p->dirX = 0.99;
        p->dirY = 0;
    }

}

static void set_plane(t_p *p)
{
    if (p->dirY == -0.99)
    {
        p->planeX = .66;
        p->planeY = 0;
    }
    else if (p->dirY == 0.99)
    {
        p->planeX = -.66;
        p->planeY = 0;
    }
    else if (p->dirX == -0.99)
    {
        p->planeX = 0;
        p->planeY = -.66;
    }
    else if (p->dirX == 0.99)
    {
        p->planeX = 0;
        p->planeY = .66;
    }
}
void    get_p_cord(t_game *game)
{
    t_p    tmp_p;
    size_t      r;
    size_t      c;
    
    r = 0;
    memset(&tmp_p, 0 , sizeof(t_p));
    while (r < game->map_height)
    {
        c = 0;
        while (c < ft_strlen(game->map[r]))
        {
            if (is_p_cord(game->map[r][c]))
            {
                tmp_p.posX = (double) c + .5;
                tmp_p.posY = (double) r + .5;
                set_pos(&tmp_p, game->map[r][c]);
                set_plane(&tmp_p);
                game->map[r][c] = '0';
                game->p = tmp_p;
                return;
            }
            c++;
        }
        r++;   
    } 
}