/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:01:42 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/05 17:42:19 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_isend_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		ft_newline_index(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

/*
** s'il y a du buffer
**		s’il y a un \n
**				mettre dans line buffer jusqu’a buffer[i] == ‘\n’
**				mettre dans buffer le reste a partir de ‘\n’;
**				return (1);
**		sinon
**			mettre dans line buffer (*line = buffer)
**
**
**tant qu’il y en a a lire dans le fichier
**		s’il y a un \n
**			mettre dans line buffer jusqu’a buffer[i] == ‘\n’;
**			mettre dans buffer le reste a partir de ‘\n’;
**			return (1);
**
**		sinon
**			concatener buffer dans line
**
**return (0);
*/

int		get_next_line(int fd, char **line)
{
	static char	*buffer;
	char		*tmp;
	int			ret;
	
	if (!(line = malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (buffer)
	{
		if (ft_newline_index(buffer) >= 0)
		{
			ft_strlcpy(*line, buffer, ft_newline_index(buffer) + 1);
			tmp = buffer;
			free(buffer);
			if (!(buffer = malloc(BUFFER_SIZE + 1)))
				return (-1);
			buffer = ft_strdup(&buffer[ft_newline_index(buffer)]);
			return (1);
		}
		*line = buffer;
	}
	if (!(buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (ft_newline_index(buffer) >= 0)
		{
			ft_strlcpy(*line, buffer, ft_newline_index(buffer) + 1);
			tmp = buffer;
			free(buffer);
			if (!(buffer = malloc(BUFFER_SIZE + 1)))
				return (-1);
			buffer = ft_strdup(&buffer[ft_newline_index(buffer)]);
			return (1);
		}
		tmp = *line;;
		if (!(*line = malloc(ft_strlen(*line) + BUFFER_SIZE + 1)))
			return (-1);
		ft_strlcpy(*line, tmp, ft_strlen(tmp) + 1);
		free(tmp);
		ft_strlcat(*line, buffer, ft_strlen(*line) + ft_strlen(buffer) + 1);
	}
	return (ret);
}

#include <stdio.h>
#include <fcntl.h>
int main()
{
	int fd = open("fd.txt", O_RDONLY);
	char *line;

	while ((get_next_line(fd, &line)) > 0)
	{
		printf("\033[0;31m");
		printf("%s\n", line);
	}
	return (0);
}
