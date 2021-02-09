/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:01:42 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/09 17:06:58 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	tmp = NULL;
	*line = malloc(0);
	if (buffer)
	{
		if (ft_newline_index(buffer) != -1)
		{
			tmp = *line;
			*line = ft_strndup(buffer, ft_newline_index(buffer));
			free(tmp);
			tmp = NULL;
			tmp = buffer;
			buffer = ft_strdup(&buffer[ft_newline_index(buffer) + 1]);
			free(tmp);
			tmp = NULL;
			return (1);
		}
		else
			*line = buffer;
	}
	if (!(buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (ft_newline_index(buffer) != -1)
		{
			tmp = *line;
			*line = ft_strjoin(*line, ft_strndup(buffer, ft_newline_index(buffer)));
			free(tmp);
			tmp = NULL;
			tmp = buffer;
			buffer = ft_strdup(&buffer[ft_newline_index(buffer) + 1]);
			free(tmp);
			tmp = NULL;
			return (1);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
	}
	return (ret);
}

/*#include <stdio.h>
#include <fcntl.h>
int main()
{
	int fd = open("fd", O_RDONLY);
	//int fd = 0;
	char *line = NULL;
	int ret;

	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		printf("\033[0;31m");
		printf("ret ===> %d\n", ret);
		printf("\033[0m");
		printf("line ====> %s\n", line);
		free(line);
		ret = get_next_line(fd, &line);
	}
	printf("\033[0;31m");
	printf("ret ===> %d\n", ret);
	printf("\033[0m");
	return (0);
}
*/
