/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonnet <bbonnet@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:57:24 by bbonnet           #+#    #+#             */
/*   Updated: 2023/11/07 04:00:23 by bbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 256

//calloc strlcpy memmove strlen realloc strlcat
int strlen_char(const char *str, const char c)
{
    const char *start;

    start = str;
    while (*start && *start != c)
        ++start;
    return (start - str + (*start == c));
}

int extract_first_line_from_buffer(char **line, char *buffer)
{
    int i;

    i = strlen_char(buffer, '\n');
    if (i == 0)
        return (0);
    line = calloc((i + 1), sizeof(char));
    if (!line)
        return (-1);
    strncpy(*line, buffer, i);
    memmove(buffer, buffer + i + 1, strlen(&buffer[i + 1]));
    i = 0;
    return (1);
}



int extract_line(char *line, char *buffer, int fd)
{
    char *new_line;
    int error;
    int line_len;
    int buffer_len;

    line_len = strlen_char(line, 0);
    while(1)
    {
        error = read(fd, buffer, BUFFER_SIZE);
        if (error == -1 || error == 0)
            return (error);
        line_len += strlen_char(buffer, '\n');
        new_line = realloc(line, (line_len + 1) * sizeof(char));
        free(line);
        strncat(line, buffer, line_len + 1);
        if (line[line_len - 1] == '\n')
        return (1);
    }
}

char *get_next_line(int fd)
{
    static char *buffer;
    char        *line;
    int         status;

    if (!buffer)
    {
        buffer = calloc(BUFFER_SIZE, sizeof(char));
        if (!buffer)
            return (NULL);
    }
    status = extract_first_line_from_buffer(&line, buffer);
    if (status == 1)
        return (line);
    else if (status == -1)
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    status = extract_line(line, buffer, fd);
    if (status == -1 || (status == 0 && !line))
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    return (line);
}


int main(int argc, char **argv){
    int fd;

    //fd = open(argv[1], O_RDONLY);
    char *test;
    extract_first_line_from_buffer(&test, "commet ca va\ntout le monde\n");
    printf("%s", test);

}
