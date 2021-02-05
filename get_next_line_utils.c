/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:52:32 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/05 17:27:03 by ztouzri          ###   ########.fr       */
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(src);
	while (*dst && size)
	{
		dst++;
		len++;
		size--;
	}
	while (*src && size > 1)
	{
		*dst++ = *src++;
		size--;
	}
	if (size)
		*dst = 0;
	return (len);
}

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
