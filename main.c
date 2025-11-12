#include "cub3d.h"


int main(int ac, char **av)
{
    t_game  game;
    char    *msg;

    memset(&game, 0, sizeof(t_game));
    if (!pre_check(ac, av, &msg))
        return (0);
    if (!main_trigger(av[1], &game))
        return (0);
    
}