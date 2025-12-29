/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config_tex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziane <aziane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 21:54:06 by aziane            #+#    #+#             */
/*   Updated: 2025/12/27 21:54:06 by aziane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_path(char *line)
{
	int	i;
	int	end;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i])
		i += 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	end = ft_strlen(line);
	while (end > i && (line[end - 1] == '\n' || line[end - 1] == '\r'
			|| line[end - 1] == ' ' || line[end - 1] == '\t'))
		end--;
	return (gc_substr(line, i, end - i));
}

static int	validate_texture_file(char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(path + len - 4, ".xpm") != 0)
	{
		printf("Error\nInvalid texture extension for %s: must be .xpm\n", path);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("the path is %s\n", path);
		perror("Error\nCannot open texture path");
		return (0);
	}
	close(fd);
	return (1);
}

static t_textures	get_texture(char **tex_tokens, int *done, char *line)
{
	t_textures	t;
	char		*raw_path;

	memset(&t, 0, sizeof(t_textures));
	if (!tex_tokens || !tex_tokens[0] || !tex_tokens[1])
	{
		*done = 0;
		printf("Error\nInvalid texture line format. Expected 'ID PATH'.\n");
		return (t);
	}
	raw_path = get_path(line);
	t.path = gc_strdup(raw_path);
	if (!t.path)
	{
		*done = 0;
		perror("Error\nstrdup failed for texture path");
		return (t);
	}
	if (!validate_texture_file(t.path))
	{
		*done = 0;
		return (t);
	}
	*done = 1;
	return (t);
}

static void	assign_texture(t_config *config, t_co_type type, t_textures t,
		int *done)
{
	t_textures	*target;

	target = NULL;
	if (type == NO)
		target = &config->no_tex;
	else if (type == SO)
		target = &config->so_tex;
	else if (type == EA)
		target = &config->ea_tex;
	else if (type == WE)
		target = &config->we_tex;
	if (target)
	{
		if (target->path)
			*done = 0;
		else
			*target = t;
	}
}

int	process_tex(char **tex_tokens, t_config *config, int *done, char *line)
{
	t_textures	temp_tex;

	temp_tex = get_texture(tex_tokens, done, line);
	if (*done == 0)
		return (0);
	if (ft_strcmp(tex_tokens[0], "NO") == 0)
		assign_texture(config, NO, temp_tex, done);
	else if (ft_strcmp(tex_tokens[0], "SO") == 0)
		assign_texture(config, SO, temp_tex, done);
	else if (ft_strcmp(tex_tokens[0], "EA") == 0)
		assign_texture(config, EA, temp_tex, done);
	else if (ft_strcmp(tex_tokens[0], "WE") == 0)
		assign_texture(config, WE, temp_tex, done);
	if (*done == 0)
	{
		printf("Error\nDuplicate texture definition.\n");
		return (0);
	}
	return (1);
}
