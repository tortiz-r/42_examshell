#ifndef RIP_H
# define RIP_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

void rip(char *str, size_t pos);

size_t ft_strlen(char *s);
char *ft_strchr(char *s, int c);

#endif