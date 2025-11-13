#include "cub3d.h"

static int process_config_line(char **s_line, t_config *config)
{
    int current_line_done;

    current_line_done = 0;
    if (ft_strcmp(s_line[0], "NO") == 0 || ft_strcmp(s_line[0], "SO") == 0 ||
        ft_strcmp(s_line[0], "EA") == 0 || ft_strcmp(s_line[0], "WE") == 0)
    {
        if (!process_tex(s_line, config, &current_line_done))
            return (0);
    }
    else if (ft_strcmp(s_line[0], "F") == 0 || ft_strcmp(s_line[0], "C") == 0)
    {
        if (!process_fc(s_line, config, &current_line_done))
            return (0);
    }
    else
    {
        printf("Error\nUnknown identifier in config section: %s\n", s_line[0]);
        return (0);
    }
    if (current_line_done)
    {
        config->all_done++;
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
        else
            return (printf("Error\\nfound an empty line inside map data.\\n"), 0);
    }

    tokens = ft_split(line, ' ');
    if (!tokens)
        return (printf("Error\nft_split failed\n"), 0);
    if (game->config.all_done < 6)
    {
        if (!process_config_line(tokens, &game->config))
            return (free_split(tokens), 0);
    }
    else
    {
        printf("map\n");
            return (free_split(tokens), 0);
    }
    free_split(tokens);
    return (1);
}

int main_trigger(char *map, t_game *game)
{
    int     fd;
    char    *line;

    game->config.all_done = 0;
    game->map_started = 0;
    fd = open(map, O_RDONLY);
    if (fd < 0)
        (perror("open"), exit(EXIT_FAILURE));
    line = get_next_line(fd);
    if (line == NULL)
        printf("ikhan\n");
    while (line != NULL)
    {
        if (!parse_line(line, game))
            return (close(fd), 0);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    if (game->config.all_done == 0 && !game->map_started)
        return (printf("map file cannot be empty!\n"), 0);
    if (game->config.all_done < 6)
        return (printf("Error\nMissing one or more config id.\n"), 0);
    if (!game->map_started)
        return (printf("Error\nmap data wasn't found in file\n"));
    return (1);
}
