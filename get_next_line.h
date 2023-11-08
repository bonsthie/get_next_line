#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZES 42


int ft_strlen(const char *str);
size_t ft_strlcat(char *dest, const char *src, unsigned int size);
void *ft_memmove(void *destination, const void *source, size_t num);
char *get_next_line(int fd);

#endif
