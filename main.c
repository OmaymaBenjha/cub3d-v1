#include "cub3d.h"


int main(int ac, char **av)
{
    t_game  game;

    memset(&game, 0, sizeof(t_game));
    if (!pre_check(ac, av))
        return (0);
    if (main_trigger(av[1], &game) == 0)
        return (1);
    get_player_cord(&game);
    make_map_rectangular(&game);
    init_game(&game);
    gc_freed();
    return (0);
}