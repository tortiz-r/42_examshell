#ifndef POWERSET_H
# define POWERSET_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

# define DEBUG 0

typedef struct s_nums
{
    int     *nums;
    size_t  size;
}               t_nums;

int powerset(int ref, t_nums *input, t_nums *path, size_t index);
int	sum_condition(int ref, t_nums *path);
t_nums *alloc_path(int *nums, int size, int newsize, int newnum);
void print_path(t_nums *path);
void free_path(t_nums *path);


size_t ft_strlen(char *s);
char *ft_strchr(char *s, int c);
void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memmove(void *dest, const void *src, size_t n);
int str_append_mem(char **s1, char *s2, size_t size2);
int str_append_str(char **s1, char *s2);

#endif