#include "cub3d.h"

static int check_column_edges(t_game *game)
{
    size_t c;

    c = 0;
    while (c < game->map_width)
    {
        if (c < ft_strlen(game->map[0]) &&
            (game->map[0][c] == '0' || is_p_char(game->map[0][c])))
            return (printf("Error\nMap not closed (top edge).\n"), 0);
        if (c < ft_strlen(game->map[game->map_height - 1]) &&
            (game->map[game->map_height - 1][c] == '0' || 
            is_p_char(game->map[game->map_height - 1][c])))
            return (printf("Error\nMap not closed (bottom edge).\n"), 0);
        c++;
    }
    return (1);
}

static int check_neighbor_edges(t_game *game, size_t *r)
{
    size_t  c;
    char    current_char;

    c = 0;
    while (c < ft_strlen(game->map[(*r)]))
    {
        current_char = game->map[(*r)][c];
        if (current_char == '0' || is_p_char(current_char))
        {
            if (r == 0 || (c >= ft_strlen(game->map[(*r) - 1]) ||
                game->map[(*r) - 1][c] == ' ' || game->map[(*r) - 1][c] == '\0'))
                return (printf("Error\nMap not closed (top neighbor of '0' or p).\n"), 0);
            if ((*r) == game->map_height - 1 ||
                (c >= ft_strlen(game->map[(*r) + 1]) ||
                game->map[(*r) + 1][c] == ' ' || game->map[(*r) + 1][c] == '\0'))
                return (printf("Error\nMap not closed (bottom neighbor of '0' or p).\n"), 0);
            if (c == 0 || game->map[(*r)][c-1] == ' ')
                return (printf("Error\nMap not closed (left neighbor of '0' or p).\n"), 0);
            if (c == ft_strlen(game->map[(*r)]) - 1 || game->map[(*r)][c+1] == ' ')
                return (printf("Error\nMap not closed (right neighbor of '0' or p).\n"), 0);
        }
        c++;
    }
    return (1);
}

int check_raw_edges(t_game *game)
{
    size_t  r;
    size_t  c;
    size_t  first_non_space;
    size_t  last_non_space;

    c = 0;
    r = 0;
    first_non_space = (size_t) - 1;
    last_non_space = (size_t) - 1;
    while (r < game->map_height)
    {
        c = 0;
        while (c < ft_strlen(game->map[r]))
        {
            if (game->map[r][c] != ' ')
            {
                first_non_space = c;
                break;
            }
            c++;    
        }
        if (first_non_space != (size_t) - 1 &&
            (game->map[r][first_non_space] == '0' ||
            is_p_char(game->map[r][first_non_space])))
            return (printf("Error\nMap not closed (left edge).\n"), 0);
        c = ft_strlen(game->map[r]);
        while (c > 0)
        {
            c--;
            if (game->map[r][c] != ' ')
            {
                last_non_space = c;
                break;
            }
        }
        if (last_non_space != (size_t)-1 &&
            (game->map[r][last_non_space] == '0' ||
            is_p_char(game->map[r][last_non_space])))
            return (printf("Error\nMap not closed (right edge).\n"), 0); 
        if (!check_neighbor_edges(game, &r))
            return (0);
        r++;
    }
    return (1);
}

int check_map_closed(t_game *game)
{
    if (!check_column_edges(game))
        return (0);
    if (!check_raw_edges(game))
        return (0);
    return (1);
}