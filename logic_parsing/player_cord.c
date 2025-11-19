#include "cub3d.h"

static  int is_player_cord(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
static void set_pos(t_player *player, char c)
{
    if (c == 'N')
    {
        player->dirX = 0;
        player->dirY = -1;
    }
    else if (c == 'S')
    {
        player->dirX = 0;
        player->dirY = 1;
    }
    else if (c == 'W')
    {
        player->dirX = -1;
        player->dirY = 0;
    }
    else if (c == 'E')
    {
        player->dirX = 1;
        player->dirY = 0;
    }

}

static void set_plane(t_player *player)
{
    if (player->dirY == -1)
    {
        player->planeX = .66;
        player->planeY = 0;
    }
    else if (player->dirY == 1)
    {
        player->planeX = -.66;
        player->planeY = 0;
    }
    else if (player->dirX == -1)
    {
        player->planeX = 0;
        player->planeY = -.66;
    }
    else if (player->dirX == 1)
    {
        player->planeX = 0;
        player->planeY = .66;
    }
}
void    get_player_cord(t_game *game)
{
    t_player    tmp_player;
    size_t      r;
    size_t      c;
    
    r = 0;
    memset(&tmp_player, 0 , sizeof(t_player));
    while (r < game->map_height)
    {
        c = 0;
        while (c < ft_strlen(game->map[r]))
        {
            if (is_player_cord(game->map[r][c]))
            {
                tmp_player.posX = (double) c + .5;
                tmp_player.posY = (double) r + .5;
                set_pos(&tmp_player, game->map[r][c]);
                set_plane(&tmp_player);
                game->map[r][c] = '0';
                game->player = tmp_player;
                return;
            }
            c++;
        }
        r++;   
    } 
}