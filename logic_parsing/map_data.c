#include "cub3d.h"
static int is_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
static void add_line(t_game *game, char *line)
{
    char    **new_map;
    size_t  i;

    i = 0;
    if (!game->map)
    {
        game->map = (char **)malloc(sizeof(char *) * 2);
        if (!game->map)
            (perror("Error\nMalloc failed for map"), exit(EXIT_FAILURE));
        game->map[0] = ft_strdup(line);
        if (!game->map[0])
            (perror("Error\nMalloc failed for map line"), exit(EXIT_FAILURE));
        game->map[1] = NULL;
        game->map_height = 1;
    }
    else
    {
        new_map = (char **)malloc(sizeof(char *) * (game->map_height + 2));
        if (!new_map)
            (perror("Error\nMalloc failed for map"), exit(EXIT_FAILURE));
        while (i < game->map_height)
        {
            new_map[i] = game->map[i];
            i++;
        }
        new_map[i] = ft_strdup(line);
        if (!new_map)
            (perror("Error\nMalloc failed for map line"), exit(EXIT_FAILURE));
        new_map[i + 1] = NULL;
        free(game->map);
        game->map = new_map;
        game->map_height++;
    }
    if (ft_strlen(line) > game->map_width)
        game->map_width = ft_strlen(line);
}



static int validate_map_line(char *line, t_game *game)
{
    size_t  i;
    static  int p_count;

    i = 0;
    while (line[i])
    {
        if (!is_map_char(line[i]))
            return (printf("Error\nInvalid character in map: '%c\n'", line[i]), 0);
        if (is_player_char(line[i]))
        {
            p_count++;
            if (p_count > 1)
                return (printf("Error\nOnly one player start position is allowed in the map.\n"), 0);
        }
        if (line[i] == '0' || is_player_char(line[i]))
        {
            if (i > 0 && line[i - 1] == ' ')
                return (printf("Error\n'0' or player character surrounded by space on left.\n"), 0);
            if (line[i + 1] == ' ')
                return (printf("Error\n'0' or player character surrounded by space on right.\n"), 0);
        }
        i++;
    }
    game->map_started = 1;
    return (1);
}

int process_map(char *line, t_game *game)
{
    if (!validate_map_line(line, game))
        return (0);
    add_line(game, line);
    return (1);
}