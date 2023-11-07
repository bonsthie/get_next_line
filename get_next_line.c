/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonnet <bbonnet@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:57:24 by bbonnet           #+#    #+#             */
/*   Updated: 2023/11/07 13:32:21 by bbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 256

// calloc strlcpy memmove strlen realloc strlcat
int strlen_char(const char *str, const char c)
{
	const char *start;

    if (str == NULL)
        return (0);
	start = str;
	while (*start && *start != c)
		++start;
	return (start - str + (*start == c));
}

int extract_line_from_buffer(char **line, char *buffer)
{
	int buffer_len;
    int line_len;

	buffer_len = strlen_char(buffer, '\n');
	if (buffer_len == 0)
		return (0);
    if (*line == NULL)
        line_len = 0;
    else
        line_len = strlen(*line);
	*line = realloc(*line, (line_len + buffer_len + 1) * sizeof(char));
	if (!line)
		return (-1);
	strncpy(*line, buffer, buffer_len);
	if (buffer[buffer_len - 1] == '\n')
		memmove(buffer, buffer + buffer_len + 1, strlen(buffer) - buffer_len - 1);
	return (1);
}

char *get_next_line(int fd)
{
	static char *buffer;
	char        *line;
	int          status;

	if (!buffer)
	{
		buffer = calloc(BUFFER_SIZE, sizeof(char));
		if (!buffer)
			return (NULL);
	}
    while(1)
    {
        status = extract_line_from_buffer(&line, buffer);
        if (status == 1)
            return (line);
        else if (status == -1)
        {
            free(buffer);
            buffer = NULL;
            return (NULL);
        }
        else if (status == 0)
            read(fd, buffer, BUFFER_SIZE);
    }
}

int main(int argc, char **argv)
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	printf("%s", get_next_line(fd));
}
