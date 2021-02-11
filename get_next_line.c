/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:01:42 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/11 17:36:04 by ztouzri          ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			res = (char*)&s[i];
			return (res);
		}
		i++;
	}
	if (s[i] == (char)c)
	{
		res = (char*)&s[i];
		return (res);
	}
	return (NULL);
}

#include <stdio.h>
int		get_next_line(int fd, char **line)
{
	char		*buffer;
	char		*tmp;
	static char	*str = NULL;
	int			ret;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || !(buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	if ((ret = 1) && str == 0)
		str = ft_strdup("\0");
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (ft_strchr(buffer, '\n'))
		{
			tmp = ft_substr(buffer, 0, ft_strchr(buffer, '\n') - buffer);
			*line = ft_strjoin(str, tmp);
			free(tmp);
			free(str);
			tmp = NULL;
			tmp = buffer;
			str = ft_strdup(ft_strchr(tmp, '\n') + 1);
			free(tmp);
			tmp = NULL;
			return (1);
		}
		tmp = str;
		str = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
	}
	return (ret);
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
	return (0);
}
