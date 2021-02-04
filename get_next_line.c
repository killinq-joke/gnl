/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:31:09 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/04 15:19:16 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*duplicate;
	size_t	i;

	if (!(duplicate = malloc(ft_strlen(s1) + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		duplicate[i] = s1[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

int		ft_newline_indexer(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	static char buffer[BUFFER_SIZE + 1];
	char		*tmp;
	int			ret;
	int			len;
	int			nlindex;

	if (fd < 0 || fd == 1 || fd == 2 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (ft_strlen(buffer))
	{
		if ((nlindex = ft_newline_indexer(buffer, '\n')) != 1)
		{
			ft_strlcat(line, buffer, ft_strlen(line) + nlindex + 1);
			tmp = &buffer[nlindex + 1];
			free(buffer);
			buffer = tmp;
			tmp = *line;
			if (!(*line = malloc(ft_strlen(tmp) + BUFFER_SIZE + 1)))
				return (-1);
			ft_strlcpy(*line, tmp);
			free(tmp);
			return (1);
		}//si fin de ligne, concatener jusqu'au \n et mettre le reste dans buffer
	}
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if ((nlindex = ft_newline_indexer(buffer, '\n')) != -1)
		{
			ft_strlcat(line, buffer, ft_strlen(line) + nlindex + 1);
			tmp = &buffer[nlindex + 1];
			free(buffer);
			buffer = tmp;
			tmp = *line;
			if (!(*line = malloc(ft_strlen(tmp) + BUFFER_SIZE + 1)))
				return (-1);
			ft_strlcpy(*line, tmp);
			free(tmp);
			return (1);
		}
	}
	return (0);
}

#include <stdio.h>
#include <fcntl.h>
int main()
{
	int ret;
	char *line;
	int fd = open("fd.txt", O_RDONLY);

	ret = get_next_line(fd, &line);
	printf("ret => %d\n", ret);
    while (ret > 0) {
        write(1, line, ft_strlen(line));
        write(1, "\n", 1);
        free(line);
        line = 0;
        ret = get_next_line(fd, &line);
		printf("ret => %d\n", ret);
    }
    if (ret == 0) {
        write(1, line, ft_strlen(line));
        write(1, "\n", 1);
        free(line);
        line = 0;
    }
}
