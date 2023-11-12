/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonnet <bbonnet@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:03:58 by bbonnet           #+#    #+#             */
/*   Updated: 2023/11/12 23:10:35 by bbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(const char *str)
{
	const char *start;

	start = str;
	while (*start)
		++start;
	return (start - str);
}

size_t ft_strlcat(char *dest, const char *src, unsigned int size)
{
	size_t dest_len;
	size_t src_len;
	size_t i;

	if (!size)
		return (ft_strlen(src));
	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_len >= size)
		return (src_len + size);
	while (src[i] && dest_len + i < size - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = 0;
	return (dest_len + src_len);
}

void *ft_memmove(void *destination, const void *source, size_t num)
{
	unsigned char *src;
	unsigned char *dest;

	src = (unsigned char *) source;
	dest = (unsigned char *) destination;
	if (src == dest)
		return (destination);
	if (src > dest)
	{
		while (num--)
			*dest++ = *src++;
	}
	else
	{
		src += num;
		dest += num;
		while (num--)
			*(--dest) = *(--src);
	}
	return (destination);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_realloc_str(char *str, size_t new_size)
{
	if (new_size == 0)
	{
		free(str);
		return NULL;
	}

	if (!str)
		return malloc(new_size * sizeof(char));
	void *new_ptr = malloc(new_size);
	if (new_ptr)
	{
		ft_strcpy(new_ptr, str);
		free(str);
	}
	return new_ptr;
}
