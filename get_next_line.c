/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:01:42 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/15 10:16:07 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int		nlindex(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

#include <stdio.h>
int		get_next_line(int fd, char **line)
{
	char		*buffer;
	char		*tmp;
	static char	*str;
	int			ret;

	if (fd < 0 || BUFFER_SIZE < 1 || !line ||
			!(buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	if ((ret = 1) && !str)
		str = ft_strdup("");
	while (nlindex(str) == -1 && ((ret = read(fd, buffer, BUFFER_SIZE)) > 0))
	{
		buffer[ret] = '\0';
		tmp = ft_strjoin(str, buffer);
		free(str);
		str = tmp;
	}
	if (ret == 0)
		*line = ft_strdup(str);
	else if (ret > 0)
		*line = ft_substr(str, 0, nlindex(str));
	else
		return (-1);
	str = ft_strdup(&str[ft_strlen(*line) + 1]);
	return (ret != 0);
}

#include <stdio.h>
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
	printf("line ====> %s\n", line);
	free(line);
	return (0);
}
