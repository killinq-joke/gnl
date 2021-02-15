/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:01:42 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/15 17:13:25 by ztouzri          ###   ########.fr       */
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

int		ft_free(char **str)
{
	int	i;

	i = 0;
	if (*str)
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	return (0);
}

int		ft_reader(int fd, char **str, char *buffer)
{
	int		ret;
	char	*tmp;

	ret = 1;
	while (nlindex(*str) == -1 && (ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		tmp = ft_strjoin(*str, buffer);
		ft_free(str);
		*str = tmp;
	}
	ft_free(&buffer);
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char *str = NULL;
	char		*tmp;
	char		*buffer;
	int			ret;

	if ((fd < 0 || fd > 255 || BUFFER_SIZE < 1
				|| !line || !(buffer = malloc(BUFFER_SIZE + 1))))
		return (-1);
	*line = NULL;
	str == NULL ? str = ft_strdup("\0") : NULL;
	ret = ft_reader(fd, &str, buffer);
	if (ret == 0)
		*line = ft_strdup(str);
	else if (ret > 0)
		*line = ft_substr(str, 0, nlindex(str));
	else
		return (-1);
	tmp = ft_strdup(&str[nlindex(str) + 1]);
	ft_free(&str);
	str = tmp;
	if (ret == 0)
		ft_free(&str);
	return (ret == 0 ? 0 : 1);
}
