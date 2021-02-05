/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:01:42 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/05 16:25:39 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
**		mettre dans line buffer (*line = buffer)
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
	
	if (!(line = malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (buffer)
	{
		if (ft_newline_index(buffer) >= 0)
		{
			ft_strlcpy(line, buffer, ft_newline_index(buffer) + 1);
			return (1);
		}
		*line = buffer;
	}
	if (!(buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (ft_newline_index(buffer) >= 0)
		{
			ft_strlcpy(line, buffer, ft_newline_index(buffer) + 1);
			
			return (1);
		}
	}
	return (ret);
}
