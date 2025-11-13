#include "cub3d.h"
static t_color get_representation(char **tokens, int *line)
{
    t_color c;
    int     r;
    int     g;
    int     b;

    memset(&c, 0, sizeof(t_color));
    r = atoi(tokens[0]);
    g = atoi(tokens[1]);
    b = atoi(tokens[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 )
    {
        *line = 0;
        return (printf("Error\nrgb is out of range.\n"), c);
    }
    c.r = r;
    c.g = g;
    c.b = b;
    c.rgb = (c.r << 16) | (c.g << 8) | c.b;
    return (c);
}
static void    fill_color(t_config *config, t_co_type type, char **rgb_tokens, int *line)
{
    t_color tmp_color;

    tmp_color = get_representation(rgb_tokens, line);
    if (type == F)
        config->f_color = tmp_color;
    else    
        config->c_color = tmp_color;
    if (line == 0)
        return;
}
int process_fc(char **fc_tokens, t_config *config, int *current_line_done)
{
    char    **rgb;

    *current_line_done = 1;
    if (!fc_tokens[1])
        return (printf("Error\n missing rgb representation for %s...\n", fc_tokens[0]), 0);
    rgb = ft_split(fc_tokens[1], ',');
    if (!rgb)
        return (printf("Error\nft_split failed!\n"));
    if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3] != NULL)
        return (printf("Error\ninvalid rgb representation\n"));
    if (ft_strcmp(fc_tokens[0], "F") == 0)
        fill_color(config, F, rgb, current_line_done);
    else if (ft_strcmp(fc_tokens[0], "C") == 0)
        fill_color(config, C, rgb, current_line_done);
    if (!(*current_line_done))
        return (0);
    return (1);
}