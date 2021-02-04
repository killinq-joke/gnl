/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:33:54 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/03 16:32:35 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (!dst || !src)
		return (0);
	while (size > 0 && src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	new_len;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	new_len = ft_strlen(s) - start;
	if (new_len < len)
		len = new_len;
	if (!(substr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
