#include "cub3d.h"

int key_handler(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
    {
        exit(0);
    }
    if (keycode == KEY_W)
        move_forward(game);
    if (keycode == KEY_S)
        move_backward(game);
    if (keycode == KEY_LEFT)
        rotate_left(game);
    if (keycode == KEY_RIGHT)
        rotate_right(game);
    if (keycode == KEY_A)
        move_left(game);
    if (keycode == KEY_D)
        move_right(game);
        
    return (0);
}