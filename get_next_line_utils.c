/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonnet <bbonnet@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:03:58 by bbonnet           #+#    #+#             */
/*   Updated: 2023/11/07 21:08:15 by bbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stddef.h>

int ft_strlen(const char *str)
{
	const char *start;

    start = str;
    while(*start)
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
