# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

/*
 * allowed functs:
 * atoi, printf, fprintf, malloc, calloc, realloc, free, stdout, write
 * 
*/

void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memmove(void *dest, const void *src, size_t n);

void print_nums(int *nums, int size)
{
	fprintf(stdout, "nums: ");
	int i = 0;
	while (i < size)
	{
		fprintf(stdout, "%i ", nums[i]);
		i++;
	}
	fprintf(stdout, "\n");
}

// Ret: TRUE or FALSE
int sums_up(int ref, int *src, int src_len)
{
	int i = 0;
	int result = 0;

	if (src_len == 0)
		return 0;

	while (i < src_len)
	{
		result += src[i];
		i++;
	}
	if (result == ref)
		return 1;
	else
		return 0;

}

void powerset(int ref, int *nums, int nums_len, int pos, int *src, int src_len)
{
	// Base case
	if (pos == nums_len)
	{
		if (!sums_up(ref, src, src_len))
		{
			if (src)
				free(src);
			return;
		}

		// fprintf(stdout, "Base case!");
		// print_nums(src, src_len);
		if (src)
			fprintf(stdout, "%i", src[0]);
		int i_print = 1;
		while (i_print < src_len)
		{
			fprintf(stdout, " %i", src[i_print]);
			i_print++;
		}
		fprintf(stdout, "\n");

		if (src)
			free(src);
		return;
	}

	// CHOICE YES
	int *new_src = malloc(sizeof(int) * (src_len + 1));
	if (!new_src)
		return;
	int i = 0;
	while (i < src_len)
	{
		new_src[i] = src[i];
		i++;
	}
	new_src[i] = nums[pos];
	powerset(ref, nums, nums_len, pos + 1, new_src, src_len + 1);

	// CHOICE NO
	int *src_cpy = malloc(sizeof(int) * src_len);
	if (!src_cpy)
		return;
	i = 0;
	while (i < src_len)
	{
		src_cpy[i] = src[i];
		i++;
	}
	powerset(ref, nums, nums_len, pos + 1, src_cpy, src_len);

	return;

}

int main(int argc, char **argv)
{
	if (argc <= 2)
		return 1;

	int ref = atoi(argv[1]);
	int *nums = malloc(sizeof(int) * argc - 2);
	if (!nums)
		return 1;
	int size = argc - 2;

	int i = 0;
	while (i < size)
	{
		nums[i] = atoi(argv[i + 2]);
		i++;
	}

	// fprintf(stdout, "ref: %i\n", ref);
	// print_nums(nums, size);

	if (ref == 0)
		fprintf(stdout, "\n");
		
	powerset(ref, nums, size, 0, NULL, 0);
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