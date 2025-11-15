#include "cub3d.h"

static int process_config_line(char **s_line, t_game *game, char *line)
{
    int current_line_done;

    current_line_done = 0;
    if (ft_strcmp(s_line[0], "NO") == 0 || ft_strcmp(s_line[0], "SO") == 0 ||
        ft_strcmp(s_line[0], "EA") == 0 || ft_strcmp(s_line[0], "WE") == 0)
    {
        if (!process_tex(s_line, &game->config, &current_line_done))
            return (0);
    }
    else if (ft_strcmp(s_line[0], "F") == 0 || ft_strcmp(s_line[0], "C") == 0)
    {
        if (!process_fc(s_line, &game->config, &current_line_done))
            return (0);
    }
    else
    {
       if (process_map(line, game))
       {
            if (game->config.all_done < 6)
                return (printf("Error\nmap data found before or within the map config\n"), 0);
       }
       else 
       {
            if (!game->map_started)
                printf("Error\nInvalid texture identifier: %s\n", s_line[0]);
            return (0);
       }
    }
    if (current_line_done)
    {
        game->config.all_done++;
    }
    return (1);
}
static int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

static int is_empty(char *line)
{
    if (!line)
        return (1); 
    int i = 0;
    while (line[i])
    {
        if (!ft_isspace(line[i])) 
            return (0);
        i++;
    }
    return (1);
}

static int parse_line(char *line, t_game *game)
{
    char    **tokens;

    if (is_empty(line))
    {
        if (!game->map_started)
            return (1);
        else if (game->map_started && !game->map_ended)
        {
            game->map_started = 0;
            game->map_ended = 1;
            return 1;
        }
    }
    else if(game->map_ended)
        return (printf("Error\nfound an empty line inside map data.\n"), 0);
    tokens = ft_split(line, ' ');
    if (!tokens)
        return (printf("Error\nft_split failed\n"), 0);
    if (!process_config_line(tokens, game, line))
            return (free_split(tokens), 0);
    free_split(tokens);
    return (1);
}

int main_trigger(char *map, t_game *game)
{
    int     fd;
    char    *line;
    char    *trimed_line;

    game->config.all_done = 0;
    game->map_started = 0;
    game->map = NULL;
    game->map_width = 0;
    game->map_height = 0;
    game->map_ended = 0;
    fd = open(map, O_RDONLY);
    if (fd < 0)
        (perror("open"), exit(EXIT_FAILURE));
    line = get_next_line(fd);
    while (line != NULL)
    {
        trimed_line = ft_strtrim_newline(line);
        if (!trimed_line)
            return (printf("ERROR\nstriming line failed!\n"), free(line), close(fd), 0);
        if (!parse_line(trimed_line, game))
            return (free(line), free(trimed_line), close(fd), 0);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    if (game->config.all_done == 0 && !game->map_started)
        return (printf("map file cannot be empty!\n"), 0);
    if (game->config.all_done < 6)
        return (printf("Error\nMissing one or more config id.\n"), 0);
    if (!game->map_started && !game->map_ended)
        return (printf("Error\nmap data wasn't found in file\n"));
    if (check_map_closed(game))
        return (0);
    return (1);
}
