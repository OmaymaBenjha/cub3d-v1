#include "cub3d.h"

// 1. Move Forward (W)
void    move_forward(t_game *game)
{
    // Calculate new X position
    double new_x = game->player.posX + game->player.dirX * MOVESPEED;
    // Calculate new Y position
    double new_y = game->player.posY + game->player.dirY * MOVESPEED;

    // Check collision for X (Horizontal)
    if (game->map[(int)game->player.posY][(int)new_x] != '1')
        game->player.posX = new_x;

    // Check collision for Y (Vertical)
    if (game->map[(int)new_y][(int)game->player.posX] != '1')
        game->player.posY = new_y;
}

// 2. Move Backward (S)
void    move_backward(t_game *game)
{
    double new_x = game->player.posX - game->player.dirX * MOVESPEED;
    double new_y = game->player.posY - game->player.dirY * MOVESPEED;

    if (game->map[(int)game->player.posY][(int)new_x] != '1')
        game->player.posX = new_x;

    if (game->map[(int)new_y][(int)game->player.posX] != '1')
        game->player.posY = new_y;
}

// 3. Rotate Left (Left Arrow)
// We rotate BOTH direction and plane vectors
void    rotate_left(t_game *game)
{
    double oldDirX = game->player.dirX;
    double oldPlaneX = game->player.planeX;

    // Rotate Direction
    game->player.dirX = game->player.dirX * cos(-ROTSPEED) - game->player.dirY * sin(-ROTSPEED);
    game->player.dirY = oldDirX * sin(-ROTSPEED) + game->player.dirY * cos(-ROTSPEED);

    // Rotate Camera Plane
    game->player.planeX = game->player.planeX * cos(-ROTSPEED) - game->player.planeY * sin(-ROTSPEED);
    game->player.planeY = oldPlaneX * sin(-ROTSPEED) + game->player.planeY * cos(-ROTSPEED);
}

// 4. Rotate Right (Right Arrow)
void    rotate_right(t_game *game)
{
    double oldDirX = game->player.dirX;
    double oldPlaneX = game->player.planeX;

    // Rotate Direction
    game->player.dirX = game->player.dirX * cos(ROTSPEED) - game->player.dirY * sin(ROTSPEED);
    game->player.dirY = oldDirX * sin(ROTSPEED) + game->player.dirY * cos(ROTSPEED);

    // Rotate Camera Plane
    game->player.planeX = game->player.planeX * cos(ROTSPEED) - game->player.planeY * sin(ROTSPEED);
    game->player.planeY = oldPlaneX * sin(ROTSPEED) + game->player.planeY * cos(ROTSPEED);
}

// 5. Strafe Left (A) - Bonus but good to have
void    move_left(t_game *game)
{
    // Direction vector rotated 90 degrees is (-dirY, dirX)
    double new_x = game->player.posX - game->player.planeX * MOVESPEED;
    double new_y = game->player.posY - game->player.planeY * MOVESPEED;

    if (game->map[(int)game->player.posY][(int)new_x] != '1')
        game->player.posX = new_x;
    if (game->map[(int)new_y][(int)game->player.posX] != '1')
        game->player.posY = new_y;
}

// 6. Strafe Right (D) - Bonus but good to have
void    move_right(t_game *game)
{
    double new_x = game->player.posX + game->player.planeX * MOVESPEED;
    double new_y = game->player.posY + game->player.planeY * MOVESPEED;

    if (game->map[(int)game->player.posY][(int)new_x] != '1')
        game->player.posX = new_x;
    if (game->map[(int)new_y][(int)game->player.posX] != '1')
        game->player.posY = new_y;
}