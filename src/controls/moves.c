#include "cub3d.h"
#include "cub3d_bonus.h"

void move_forward(t_game *game)
{
    int old_x = (int)game->player.posX;
    int old_y = (int)game->player.posY;
    double new_x = game->player.posX + game->player.dirX * MOVESPEED;
    double new_y = game->player.posY + game->player.dirY * MOVESPEED;
    if (game->map[(int)game->player.posY][(int)new_x] != '1' && game->map[(int)game->player.posY][(int)new_x] != 'D')
        game->player.posX = new_x;
    if (game->map[(int)new_y][(int)game->player.posX] != '1' && game->map[(int)new_y][(int)game->player.posX] != 'D')
        game->player.posY = new_y;
    if ((int)game->player.posX != old_x || (int)game->player.posY != old_y)
    {
        if (game->map[old_y][old_x] == 'O')
            game->map[old_y][old_x] = 'D';
    }
}
void move_backward(t_game *game)
{
    int old_x = (int)game->player.posX;
    int old_y = (int)game->player.posY;
    double new_x = game->player.posX - game->player.dirX * MOVESPEED;
    double new_y = game->player.posY - game->player.dirY * MOVESPEED;

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

void    rotate_left(t_game *game)
{
    double oldDirX = game->player.dirX;
    double oldPlaneX = game->player.planeX;

    game->player.dirX = game->player.dirX * cos(-ROTSPEED) - game->player.dirY * sin(-ROTSPEED);
    game->player.dirY = oldDirX * sin(-ROTSPEED) + game->player.dirY * cos(-ROTSPEED);

    game->player.planeX = game->player.planeX * cos(-ROTSPEED) - game->player.planeY * sin(-ROTSPEED);
    game->player.planeY = oldPlaneX * sin(-ROTSPEED) + game->player.planeY * cos(-ROTSPEED);
}

int track_mouse_click(int button, int x, int y, t_game *game)
{
    game->mouse_x = x;
    game->mouse_y = y;
    if (button  == 1 && check_mouse_event_bound(game, game->menu.start_rect))
    {
        if (game->game_state == 0)
            game->game_state = 1;
    }
        
    else if (button  == 1 && check_mouse_event_bound(game, game->menu.exit_rect))
    {
        if (game->game_state  == 0)
            handle_exit(game);
    }
    return (0);
}
void toggle_door(t_game *game)
{
    int target_x = (int)(game->player.posX + game->player.dirX * 1.04);
    int target_y = (int)(game->player.posY + game->player.dirY * 1.04);

    if (game->map[target_y][target_x] == 'D')
	{
		game->map[target_y][target_x] = 'O';
		// game->door_state = 1;
	}
    // if (game->door_state == 1)
	// 	game->map[target_y][target_x] = 'D';
}
