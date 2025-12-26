#include "cub3d.h"


void    rotate_right(t_game *game)
{
    double oldDirX = game->player.dirX;
    double oldPlaneX = game->player.planeX;

    game->player.dirX = game->player.dirX * cos(ROTSPEED) - game->player.dirY * sin(ROTSPEED);
    game->player.dirY = oldDirX * sin(ROTSPEED) + game->player.dirY * cos(ROTSPEED);

    game->player.planeX = game->player.planeX * cos(ROTSPEED) - game->player.planeY * sin(ROTSPEED);
    game->player.planeY = oldPlaneX * sin(ROTSPEED) + game->player.planeY * cos(ROTSPEED);
}

void move_left(t_game *game)
{
    int old_x = (int)game->player.posX;
    int old_y = (int)game->player.posY;
    double new_x = game->player.posX - game->player.planeX * MOVESPEED;
    double new_y = game->player.posY - game->player.planeY * MOVESPEED;

    if (game->map[(int)game->player.posY][(int)new_x] != '1' && 
        game->map[(int)game->player.posY][(int)new_x] != 'D')
        game->player.posX = new_x;
    if (game->map[(int)new_y][(int)game->player.posX] != '1' && 
        game->map[(int)new_y][(int)game->player.posX] != 'D')
        game->player.posY = new_y;

    if (((int)game->player.posX != old_x || (int)game->player.posY != old_y) 
        && game->map[old_y][old_x] == 'O')
        game->map[old_y][old_x] = 'D';
}


void move_right(t_game *game)
{
    int old_x = (int)game->player.posX;
    int old_y = (int)game->player.posY;
    double new_x = game->player.posX + game->player.planeX * MOVESPEED;
    double new_y = game->player.posY + game->player.planeY * MOVESPEED;

    if (game->map[(int)game->player.posY][(int)new_x] != '1' && 
        game->map[(int)game->player.posY][(int)new_x] != 'D')
        game->player.posX = new_x;
    if (game->map[(int)new_y][(int)game->player.posX] != '1' && 
        game->map[(int)new_y][(int)game->player.posX] != 'D')
        game->player.posY = new_y;

    if (((int)game->player.posX != old_x || (int)game->player.posY != old_y) 
        && game->map[old_y][old_x] == 'O')
        game->map[old_y][old_x] = 'D';
}

int track_mouse_pos(int x, int y, t_game *game)
{
    game->mouse_x = x;
    game->mouse_y = y;

    return (0);
}