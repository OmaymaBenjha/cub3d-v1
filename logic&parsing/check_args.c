#include "cub3d.h"


int is_valid_file(char *fname)
{
    char *ext;

    ext = ft_strchr(fname, '.');
    if (!ext || ft_strchr(fname, ' '))
        return (1);
    if (ft_strcmp(ext, ".cub") != 0)
        return (1);
}

int pre_check(int ac, char **av, char *msg)
{
    if (ac != 2)
    {
        printf("ERROR\nInvalid arguments!\n");
        return (0);
    }
    if (!is_valid_file(av[1]))
    {
        printf("ERROR\nInvalid map file!\n");
        return (0);
    }
}
