#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

t_textures get_texture(char **tex_tokens, int *done)
{
    t_textures  t;
    int         fd;

    ft_memset(&t, 0, sizeof(t_textures));
    if (!tex_tokens || !tex_tokens[0] || !tex_tokens[1] || tex_tokens[2] != NULL)
    {
        printf("Error\nInvalid texture line format. Expected 'IDENTIFIER PATH'.\n");
        *done = 0;
        return (t);
    }
    t.path = ft_strdup(tex_tokens[1]);
    if (!t.path)
    {
        perror("Error\nMalloc failed for texture path");
        *done = 0;
        return (t);
    }
    fd = open(t.path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error\nCannot open texture path");
        *done = 0;
        return (t);
    }
    close(fd);
    *done = 1;
    return (t);
}

void    fill_config(t_config *config, t_co_type type, char **tex_tokens, int *current_line_done)
{
    t_textures temp_tex;

    temp_tex = get_texture(tex_tokens, current_line_done);
    if (*current_line_done == 0)
        return;
    if (type == NO)
    {
        if (config->no_tex.path != NULL) { printf("Error\nDuplicate NO texture definition.\n"); *current_line_done = 0; return; }
        config->no_tex = temp_tex;
    }
    else if (type == SO)
    {
        if (config->so_tex.path != NULL) { printf("Error\nDuplicate SO texture definition.\n"); *current_line_done = 0; return; }
        config->so_tex = temp_tex;
    }
    else if (type == EA)
    {
        if (config->ea_tex.path != NULL) { printf("Error\nDuplicate EA texture definition.\n"); *current_line_done = 0; return; }
        config->ea_tex = temp_tex;
    }
    else if (type == WE)
    {
        if (config->we_tex.path != NULL) { printf("Error\nDuplicate WE texture definition.\n"); *current_line_done = 0; return; }
        config->we_tex = temp_tex;
    }
}

int process_tex(char **tex_tokens, t_config *config, int *current_line_done)
{
    *current_line_done = 0;
    if (ft_strcmp(tex_tokens[0], "NO") == 0)
        fill_config(config, NO, tex_tokens, current_line_done);
    else if (ft_strcmp(tex_tokens[0], "SO") == 0)
        fill_config(config, SO, tex_tokens, current_line_done);
    else if (ft_strcmp(tex_tokens[0], "EA") == 0)
        fill_config(config, EA, tex_tokens, current_line_done);
    else if (ft_strcmp(tex_tokens[0], "WE") == 0)
        fill_config(config, WE, tex_tokens, current_line_done);
    else
    {
        printf("Error\nInvalid texture identifier: %s\n", tex_tokens[0]);
        return (0);
    }
    if (!(*current_line_done))
        return (0);
    if (tex_tokens[2] != NULL)
    {
        printf("Error\nToo many arguments on texture line '%s %s ...'\n", tex_tokens[0], tex_tokens[1]);
        return (0);
    }
    return (1);
}

int process_fc(char **fc_tokens, t_config *config, int *current_line_done)
{
    // Placeholder for floor/ceiling color parsing logic
    // This function needs to:
    // 1. Validate tokens (e.g., "F R,G,B")
    // 2. Parse R, G, B values, validate range (0-255)
    // 3. Store in config->f_color or config->c_color
    // 4. Check for duplicates
    // 5. Set *current_line_done = 1 on success, 0 on failure
    (void)fc_tokens; // Suppress unused parameter warning
    (void)config;
    (void)current_line_done;
    printf("Error\nprocess_fc: Not implemented yet.\n");
    *current_line_done = 0;
    return (0); // Always fail until implemented
}

int process_config_line(char **s_line, t_config *config)
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

void free_split(char **arr)
{
    int i = 0;
    if (!arr) return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int is_empty_line(char *line)
{
    if (!line) return (1);
    while (*line)
    {
        if (*line != ' ' && *line != '\t' && *line != '\n')
            return (0);
        line++;
    }
    return (1);
}

int add_map_line(t_game *game, char *line)
{
    // Placeholder for map line adding logic
    // This function needs to:
    // 1. Allocate space for the line (or expand existing map array)
    // 2. Copy the line into the map
    // 3. Validate characters (1, 0, N, S, E, W, spaces)
    // 4. Update game->map_width, game->map_height
    // 5. Find and store player initial position/orientation
    (void)game;
    (void)line;
    printf("Error\nadd_map_line: Not implemented yet.\n");
    return (0); // Always fail until implemented
}

int validate_final_map(t_game *game)
{
    // Placeholder for final map validation logic
    // This function needs to:
    // 1. Check if the map is closed by walls (e.g., flood fill)
    // 2. Check for exactly one player start position
    // 3. Ensure no invalid characters anywhere
    (void)game;
    printf("Error\nvalidate_final_map: Not implemented yet.\n");
    return (0); // Always fail until implemented
}


int parse_cub_line(t_game *game, char *line, int *map_started, int *empty_line_after_config)
{
    char    **tokens;

    if (is_empty_line(line))
    {
        if (game->config.all_done >= 6 && !(*map_started))
            *empty_line_after_config = 1;
        return (1);
    }
    if (*empty_line_after_config && !(*map_started))
    {
        printf("Error\nNon-empty line after empty line before map start.\n");
        return (0);
    }

    tokens = ft_split(line, ' ');
    if (!tokens || !tokens[0])
    {
        free_split(tokens);
        printf("Error\nEmpty token or split failed for line: %s\n", line);
        return (0);
    }

    if (game->config.all_done < 6)
    {
        if (!process_config_line(tokens, &game->config))
        {
            free_split(tokens);
            return (0);
        }
    }
    else
    {
        *map_started = 1;
        if (!add_map_line(game, line))
        {
            free_split(tokens);
            return (0);
        }
    }
    free_split(tokens);
    return (1);
}

int main_trigger(char *map_file_path, t_game *game)
{
    int     fd;
    char    *line;
    int     ret;
    int     map_started = 0;
    int     empty_line_after_config = 0;

    game->config.all_done = 0; // Initialize config counter

    fd = open(map_file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    line = get_next_line(fd);
    while (line != NULL)
    {
        ret = parse_cub_line(game, line, &map_started, &empty_line_after_config);
        free(line);
        if (ret == 0)
        {
            close(fd);
            return (0);
        }
        line = get_next_line(fd);
    }
    close(fd);

    if (game->config.all_done < 6)
    {
        printf("Error\nMissing configuration items.\n");
        return (0);
    }
    if (!map_started)
    {
        printf("Error\nMap data not found in file.\n");
        return (0);
    }
    if (!validate_final_map(game))
        return (0);

    return (1);
}