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
    else if (game->config.all_done < 6)
    {
        char *line_copy;
        line_copy = gc_strdup(line);
        if (!line_copy)
            return (printf("Error\nstrdup failed!\n"),0);
        while (*line_copy)
        {
            if (!is_map_char(*line))
                break;
            line_copy++;
        }
        if (is_map_char(*line))
            return (printf("Error\nMap data found before or within the map config\n"), 0);
        return(printf("Error\nInvalid texture identifier: %s\n", s_line[0]),0);
    }
    else
    {
       if (!process_map(line, game))
            return (0);
       
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
    tokens = gc_split(line, ' ');
    if (!tokens)
        return (printf("Error\nft_split failed\n"), 0);
    if (!process_config_line(tokens, game, line))
            return (0);
    return (1);
}
static void initiate_game_struct(t_game *game)
{
    game->config.all_done = 0;
    game->map_started = 0;
    game->map = NULL;
    game->map_width = 0;
    game->map_height = 0;
    game->map_ended = 0;
    game->player_count = 0;
    game->config.c_has_been_set = 0;
    game->config.f_has_been_set = 0;
    game->map_exist = 0;
    game->game_state = 0;
    game->menu.start_rect.width = 500;
    game->menu.start_rect.height = 220;
    game->menu.exit_rect.width = 500;
    game->menu.exit_rect.height = 220;
    game->menu.start_rect.x = WIDTH / 2 - game->menu.start_rect.width - 40;
    game->menu.start_rect.y = HEIGHT / 2 ;
    game->menu.exit_rect.x = WIDTH / 2 + 40;
    game->menu.exit_rect.y = HEIGHT / 2;
    
}

static int check_game_map_state(t_game *game)
{
    if (game->player_count == 0 && game->map_exist)
        return(printf("Error\nPlayer starting position is missing in the map.\nTry: S/N/W/E.\n"),0);
    if (game->config.all_done == 0 && !game->map_started)
        return (printf("Map file cannot be empty!\n"), 0);
    if (game->config.all_done < 6)
        return (printf("Error\nMissing one or more config id.\n"), 0);
    if (!game->map_started && !game->map_ended)
        return (printf("Error\nMap data wasn't found in file\n"), 0);
    if (check_map_closed(game))
        return (0);
    return (1);
}
int main_trigger(char *map, t_game *game)
{
    int     fd;
    char    *line;
    char    *trimed_line;

    initiate_game_struct(game);
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
            return (free(line), close(fd), 0);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    if (!check_game_map_state(game))
        return (0);
    return (1);
}
