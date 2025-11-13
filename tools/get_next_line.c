#include "cub3d.h"

static char	*get_line(char *reserve)
{
	int		start;
	char	*line;
	int		i;

	start = 0;
	i = 0;
	while (reserve[i] != '\n' && reserve[i] != '\0')
		i++;
	line = ft_substr(reserve, start, i);
	return (line);
}

static char	*update_reserve(char *reserve)
{
	char	*new_res;
	int		i;

	i = 0;
	while (reserve[i] != '\n' && reserve[i] != '\0')
		i++;
	if (reserve[i] == '\n')
		i++;
	new_res = ft_substr(reserve, i, ft_strlen(reserve) - i);
	free(reserve);
	reserve = NULL;
	return (new_res);
}

static char	*helper_func(char *buffer, char *reserve, int fd)
{
	int	bytes_read;

	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(reserve), reserve = NULL, NULL);
		buffer[bytes_read] = '\0';
		reserve = ft_strjoin(reserve, buffer);
		if (!reserve)
			return (NULL);
		if (ft_strchr(reserve, '\n'))
			break ;
	}
	free(buffer);
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve = NULL;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (free(reserve), reserve = NULL, NULL);
	buffer = malloc((size_t) BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	reserve = helper_func(buffer, reserve, fd);
	if (!reserve || *reserve == '\0')
		return (free(reserve), reserve = NULL, NULL);
	line = get_line(reserve);
	reserve = update_reserve(reserve);
	return (line);
}

