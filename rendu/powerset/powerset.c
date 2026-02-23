#include "powerset.h"

/*
 * allowed functs: atoi, printf, fprintf, malloc, calloc, realloc, free, stdout, write
 * powerset debe print todas las combinaciones de nums posibles recibidos que sumen X
*/

int main(int argc, char **argv)
{
	if (argc == 1)
		return 1;
	if (!argv || !argv[0] || !argv[1])
		return 1;

	int ref = atoi(argv[1]);
	int *input = malloc(sizeof(int)*(argc - 2));
	if (!input)
		return 1;

	if (DEBUG)
		printf("ref: %i\n", ref);
	if (DEBUG)
		printf("input: ");
	size_t i = 0;
	while (argv[2 + i])
	{
		input[i] = atoi(argv[2 + i]);
		if (DEBUG)
			printf("%i, ", input[i]);
		i++;
	}
	if (DEBUG)
		printf("\n");
	if (DEBUG)
		printf("set_size = %li\n", i);

	t_nums nums;
	nums.nums = input;
	nums.size = i;
	if (ref == 0)
			
	int status = powerset(ref, &nums, NULL, 0);
	free(input);
	if (status == 0)
		return 1;
	return 0;
}

// ret 0 if error, 1 on success
int powerset(int ref, t_nums *input, t_nums *path, size_t index)
{
	if (DEBUG)
		printf("entro en powerset, index = %li\n", index);

	if (!input || !input->nums || !*(input->nums))
		return 0;

	if (!path)
	{
		path = alloc_path(NULL, 0, 0, 0);
		if (!path)
			return 0;
	}

	// BASE CONDITION
	if (path && sum_condition(ref, path))
	{
		if (DEBUG)
			printf("DEVUELVOOOO: \n");
		//DEVOLVER
		if (DEBUG)
			printf("-----------------------\n");
		size_t i = 0;
		printf("%i", path->nums[i]);
			i++;
		while (i < path->size)
		{
			printf(" %i", path->nums[i]);
			i++;
		}
		printf("\n");
		// free mi path
		return free_path(path), 1;
	}
	if (index >= input->size)
		return free_path(path), 1;

	// ELECCIONES
	int condition;
	// int futuresize = ft_strlen(path);
	// =========== SI meto input[index] en path ===========
	// -------------- COMPRUEBO CONDICIÓN --------------------
	if (path && path->size == 0)
		condition = 1;	// Si no tengo nada en path, no puedo sumar nada, así que la condición se cumple siempre
	else
		condition = sum_condition(ref, path);
	if (path && path->size == input->size && !condition)	// ................. Condición no se cumple .................
	{
		// if (DEBUG)
		// {
		// 	printf("ref = %i\n", ref);
		// 	print_path(path);
		// }
		return free_path(path), 1;
	}
	// ................. Sigo adelante .................
	if (DEBUG)
		printf("hago elección YES, index = %li\n", index);
	t_nums *newpath_YES = alloc_path(path->nums, path->size, path->size + 1, input->nums[index]);
	if (!newpath_YES)
		return 0;
	index++;
	if (!powerset(ref, input, newpath_YES, index))
		return free_path(newpath_YES), 0;
	// free_path(newpath_YES);
	// =========== NO meto input[index] en path ===========
	if (DEBUG)
		printf("hago elección NO, index = %li\n", index);
	t_nums *newpath_NO = alloc_path(path->nums, path->size, path->size, 0);
	if (!powerset(ref, input, newpath_NO, index))
		return free_path(newpath_NO), 0;
	// free_path(newpath_NO);
	free_path(path);
	return 1;
}

t_nums *alloc_path(int *nums, int size, int newsize, int newnum)
{
	t_nums *path;

	path = malloc(sizeof(t_nums));
	if (!path)
		return NULL;
	int i = 0;
	int n = size;
	if (newsize < size)
		n = newsize;
	if (!nums && size == 0 && newsize == 0)
	{
		path->nums = NULL;
		path->size = 0;
	}
	else
	{
		path->nums = malloc(sizeof(int)*newsize);
		if (!path->nums)
			return free(path), NULL;
		while (i < n)
		{
			path->nums[i] = nums[i];
			i++;
		}
		if (newsize == size + 1)
			path->nums[i] = newnum;
		path->size = newsize;
	}
	if (DEBUG)
	{
		printf("alloc_path: size = %i, newsize = %i, newnum = %i\n", size, newsize, newnum);
		print_path(path);
	}
	return path;
}

// Rets TRUE or FALSE
int	sum_condition(int ref, t_nums *path)
{
	size_t i = 0;
	int total = 0;
	if (!path || !path->nums)
		return 0;
	while (i < path->size)
	{
		total += path->nums[i];
		i++;
	}
	if (total == ref)
		return 1;
	else
		return 0;
}

void free_path(t_nums *path)
{
	if (path)
	{
		if (path->nums)
			free(path->nums);
		free(path);
	}
}

void print_path(t_nums *path)
{
	if (DEBUG)
	{
		printf("path: size = %li\n", path ? path->size : 0);
		if (path && path->nums)
		{
			size_t i = 0;
			while (i < path->size)
			{
				printf("%i, ", path->nums[i]);
				i++;
			}
			printf("\n");
		}
	}
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

char *ft_strchr(char *s, int c)
{
	int i = 0;
	if (!s)
		return NULL;
	while(s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return s + i;
	else
		return NULL;
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
	if (!dest || !src)
		return NULL;
	if (dest < src)
		return ft_memcpy(dest, src, n);
	else if (dest > src)
	{
		size_t i = 0;
		while (i < n)
		{
			((char *)dest)[n - i - 1] = ((char *)src)[n - i - 1];
			i++;
		}
	}
	else // (dest == src)
		return dest;
	return dest;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	if (*s1)
		free(*s1);
	*s1 = tmp;
	return 1; 
}

int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}
