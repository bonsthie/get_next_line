/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:57:24 by bbonnet           #+#    #+#             */
/*   Updated: 2023/11/10 18:49:49 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// realloc
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

int extract_line_from_buffer(char **line, char *buffer, int *line_len)
{
	int   buffer_len;
	char *new_line;

	buffer_len = strlen_char(buffer, '\n');
	if (buffer_len == 0)
		return (0);
	*line_len += buffer_len;
	new_line = ft_realloc(*line, (*line_len + 1) * sizeof(char));
	if (!new_line)
		return (-1);
	if (*line == NULL)
		new_line[0] = 0;
	ft_strlcat(new_line, buffer, *line_len + 1);
    new_line[*line_len] = '\0';
	*line = new_line;
	if (buffer[buffer_len - 1] == '\n')
	{
		ft_memmove(buffer, buffer + buffer_len, BUFFER_SIZE - buffer_len + 1);
		return (1);
	}
	buffer[0] = 0;
	return (2);
}

int add_to_buffer(int fd, char *buffer, char **line)
{
	int read_bytes;

	read_bytes = 0;
	if (buffer[0] == 0)
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes < 0)
		return (-1);
	buffer[read_bytes] = 0;
	if (read_bytes == 0)
	{
		if (line == NULL || *line == 0)
			return (-1);
		return (1);
	}
	return (0);
}

char *free_line(char *line)
{
	free(line);
	line = NULL;
	return (NULL);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	char       *line;
	int         line_len;
	int         status;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line_len = 0;
	line = NULL;
	while (1)
	{
		status = extract_line_from_buffer(&line, buffer, &line_len);
		if (status == 1)
			return (line);
		else if (status == -1)
			return (free_line(line));
		status = add_to_buffer(fd, buffer, &line);
		if (status == -1)
			return (NULL);
		if (status == 1)
			return (line);
	}
}

