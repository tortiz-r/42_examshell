#include "subsets.h"

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

	printf("input: ");
	size_t i = 0;
	while (argv[2 + i])
	{
		input[i] = atoi(argv[2 + i]);
		printf("%i, ", input[i]);
		i++;
	}
	printf("\n");
	printf("set_size = %li\n", i);

	t_nums nums;
	nums.nums = input;
	nums.size = i;
	int status = subsets(ref, &nums, NULL, 0);
	if (status == 1)
		return 1;
	return 0;
}

// ret 0 if error, 1 on success
int subsets(int ref, t_nums *input, t_nums *path, size_t index)
{
	if (DEBUG)
		printf("entro en subsets, index = %li\n", index);

	if (!input || !*input)
		return 0;

	if (!path)
	{
		path = malloc(sizeof(t_nums));
		if (!path)
			return 0;
		path->nums = NULL;
		path->size = 0;
	}
	// BASE CONDITION
	if (index == input->size && sum_condition(ref, path))
	{
		if (DEBUG)
			printf("DEVUELVOOOO: \n");
		//DEVOLVER
		printf("-----------------------\n");
		// free mi path
		if (path)
		{
			if (path->nums)
				free(path->nums);
			free(path);
		}
		return 1;
	}

	// ELECCIONES
	int futuresize = ft_strlen(path);
	// =========== SI meto input[index] en path ===========
	// -------------- COMPRUEBO CONDICIÓN --------------------
	// ................. Condición no se cumple .................

	// ................. Condición se cumple .................
		// añado input[index] a path
	// newpath_YES = NULL;
	// str_append_mem(newpath_YES, path, path->size)
	// str_append_mem(newpath_YES, input[index], path->size - index)
	index++;
	if (!subsets(input, newpath_YES, index))
		return 0;
	// UNDO CHOICE:
	// newpath_NO = NULL;
	// str_append_mem(newpath_NO, path, path->size)

	// =========== NO meto input[index] en path ===========
	if (!subsets(input, newpath_NO, index))
		return 0;
	return 1;
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
