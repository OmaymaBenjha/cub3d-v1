/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziane <aziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:58:21 by aziane            #+#    #+#             */
/*   Updated: 2025/12/22 11:58:21 by aziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_file(char *fname)
{
	int		len;

	len = ft_strlen(fname);
	if (len < 4)
		return (0);
	if (ft_strcmp(fname + len - 4, ".cub") != 0)
		return (0);
	if (ft_strchr(fname, ' '))
		return (0);
	return (1);
}

int	pre_check(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\n");
		printf("Few arguments!\nUsage: ./cub3d [./path_to_the_map_file]\n]");
		return (0);
	}
	if (!is_valid_file(av[1]))
	{
		printf("ERROR\nInvalid map file!\n");
		return (0);
	}
	return (1);
}
