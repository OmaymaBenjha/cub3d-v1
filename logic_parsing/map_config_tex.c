#include "cub3d.h"
static char *get_path(char *line)
{
    int i;
    int end;

    i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (line[i])
        i += 2;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    end = ft_strlen(line);
    while (end > i && (line[end - 1] == '\n' || line[end - 1] == '\r' || 
                       line[end - 1] == ' ' || line[end - 1] == '\t'))
        end--;
    return (gc_substr(line, i, end - i));
}
static t_textures get_texture(char **tex_tokens, int *done, char *line)
{
    t_textures  t;
    int         fd;
    char        *raw_path; 

    memset(&t, 0, sizeof(t_textures));
    if (!tex_tokens || !tex_tokens[0] || !tex_tokens[1])
    {
        *done = 0;
        return ( printf("Error\nInvalid texture line format. Expected 'IDENTIFIER PATH'.\n"), t);
    }
    raw_path = get_path(line);
    t.path = gc_strdup(raw_path);
    if (!t.path)
    {
        *done = 0;
        return (perror("Error\nstrdup failed for texture path"), t);
    }
    fd = open(t.path, O_RDONLY);
    if (fd < 0)
    {
        *done = 0;
        return (perror("Error\nCannot open texture path"), t);
    }
    close(fd);
    *done = 1;
    return (t);
}
static void    fill_config(t_config *config, t_co_type type, char **tex_tokens, int *current_line_done, char *line)
{
    t_textures temp_tex;

    temp_tex = get_texture(tex_tokens, current_line_done, line);
    if (*current_line_done == 0)
        return;
    if (type == NO)
    {
        if (config->no_tex.path != NULL) 
        { 
            printf("Error\nDuplicate NO texture definition.\n"); 
            *current_line_done = 0; 
            return; 
        }
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

int process_tex(char **tex_tokens, t_config *config, int *current_line_done, char *line)
{

    *current_line_done = 0;
    if (ft_strcmp(tex_tokens[0], "NO") == 0)
        fill_config(config, NO, tex_tokens, current_line_done, line);
    else if (ft_strcmp(tex_tokens[0], "SO") == 0)
        fill_config(config, SO, tex_tokens, current_line_done, line);
    else if (ft_strcmp(tex_tokens[0], "EA") == 0)
        fill_config(config, EA, tex_tokens, current_line_done, line);
    else if (ft_strcmp(tex_tokens[0], "WE") == 0)
        fill_config(config, WE, tex_tokens, current_line_done, line);
    if (!(*current_line_done))
        return (0);
    return (1);
}
