# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>


/*
 * allowed functs:
 * puts, malloc, calloc, realloc, free, write
 * 
*/

char *str_cpy(char *str);
size_t ft_strlen(char *s);
void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memmove(void *dest, const void *src, size_t n);

void swap(char *a, char *b)
{
	char tmp = *a;

	*a = *b;
	*b = tmp;
}

// Sort por referencia, no hace malloc
void bubble_sort(char *str)
{
	size_t i;
	size_t j;
	int flag = 0;
	size_t len = ft_strlen(str);

	if (!str || !*str || len < 2)
		return;

	while (!flag)
	{
		i = 0;
		while (i < len)
		{
			j = i + 1;
			while (j < len)
			{
				if (str[i] > str[j])
				{
					swap(str + i, str + j);
					flag = 0;
				}
				else
					flag = 1;
				j++;
			}
			i++;
		}
	}
	// printf("sorted = %s\n", str);
}

void permutations(char *src, size_t pos)
{
	// printf("POS = %li, src = %s\n", pos, src);

	if (pos == ft_strlen(src))
	{
		puts(src);
		free(src);
		// printf("=========================================\n");
		return;
	}
	// CHOICE NO interc src[pos]
	// Le mando la misma src
	size_t i = pos;

	char *new_src;
	new_src = str_cpy(src);
	permutations(new_src, pos + 1);

	// CHOICE SI interc [pos] con el resto:
	i++;

	while (i < ft_strlen(src))
	{
		new_src = str_cpy(src);
		if (!new_src)
			return;
		// printf("pos= %lu, i = %lu, src_cpy: %s\n", pos, i, new_src);
		// printf("swap: %c con %c \n", new_src[pos], new_src[i]);
		swap(new_src + pos, new_src + i);
		// printf("post_swap: %s\n", new_src);
		// printf("sort desde %s\n", new_src + pos + 1);
		bubble_sort(new_src + pos + 1);
		// printf("post_sort: %s\n--------------------\n", new_src);
		permutations(new_src, pos + 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	char *raw = argv[1];

	char *str = str_cpy(raw);
	if (!str)
		return 1;

	// printf("pre_sort = %s\n", str);
	bubble_sort(str);
	// printf("post_sort = %s\n", str);

	permutations(str, 0);
	// free(str);

	return 0;
}


/******************************************************/

char *str_cpy(char *str)
{
	char *src = malloc(ft_strlen(str) + 1);
	if (!src)
		return NULL;
	src = ft_memmove(src, str, ft_strlen(str) + 1);
	return src;
}

size_t ft_strlen(char *s)
{
	size_t res = 0;
	if (!s)
		return res;
	while (s[res])
		res++;
	return res;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;

	while(i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return dest;
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest < src)
		return ft_memcpy(dest, src, n);
	else if (dest == src)
		return dest;
	size_t i = 0;
	while (i < n)
	{
		((char *)dest)[n - i - 1] = ((char *)src)[n - i - 1];
		i++;
	}
	return dest;
}