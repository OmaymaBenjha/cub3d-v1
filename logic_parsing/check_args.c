#include "cub3d.h"

static int is_valid_file(char *fname)
{
    char *ext;

    ext = ft_strchr(fname, '.');
    if (!ext || ft_strchr(fname, ' '))
        return (0);
    if (ft_strcmp(ext, ".cub") != 0)
        return (0);
    return (1);
}

int pre_check(int ac, char **av)
{
    if (ac != 2)
    {
        printf("ERROR\nFew arguments!\nUsage: ./cub3d [./path_to_the_map_file]\n]");
        return (0);
    }
    if (!is_valid_file(av[1]))
    {
        printf("ERROR\nInvalid map file!\n");
        return (0);
    }
    return (1);
}
