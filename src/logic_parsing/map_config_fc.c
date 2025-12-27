/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config_fc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 21:54:03 by oben-jha          #+#    #+#             */
/*   Updated: 2025/12/27 21:54:03 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	assign_color(t_config *config, t_color c, t_co_type type, int *line)
{
	if (type == F)
	{
		if (config->f_has_been_set == 1)
		{
			printf("Error\nDuplicate F rgb representation!\n");
			*line = 0;
		}
		config->f_color = c;
		if (line)
			config->f_has_been_set++;
	}
	else
	{
		if (config->c_has_been_set == 1)
		{
			printf("Error\nDuplicate C rgb representation!\n");
			*line = 0;
		}
		config->c_color = c;
		if (line)
			config->c_has_been_set++;
	}
}

static void	fill_color(t_config *config, t_co_type type, char **rgb_tokens,
		int *line)
{
	t_color	tmp_color;

	tmp_color = get_representation(rgb_tokens, line);
	assign_color(config, tmp_color, type, line);
	if (*line == 0)
		return ;
}

static int	parse_rgb(char *merged, char ***rgb)
{
	int	i;
	int	fields_count;

	i = 0;
	fields_count = 0;
	while (merged[i])
	{
		if (merged[i] == ',')
			fields_count++;
		i++;
	}
	if (fields_count != 2)
		return (printf("Error\nInvalid rgb representation\n"), 0);
	*rgb = gc_split(merged, ',');
	if (!*rgb)
		return (printf("Error\nft_split failed!\n"), 0);
	return (1);
}

int	process_fc(char **fc_tokens, t_config *config, int *current_line_done)
{
	char	*merged;
	char	**rgb;

	*current_line_done = 1;
	if (!fc_tokens[1])
		return (printf("Error\nMissing rgb for %s\n", fc_tokens[0]), 0);
	merged = join_tokens(fc_tokens);
	if (!merged)
		return (printf("Error\nmalloc failed\n"), 0);
	if (!parse_rgb(merged, &rgb))
		return (0);
	if (!not_valid_num(rgb))
		return (0);
	if (ft_strcmp(fc_tokens[0], "F") == 0)
		fill_color(config, F, rgb, current_line_done);
	else
		fill_color(config, C, rgb, current_line_done);
	return (*current_line_done);
}
