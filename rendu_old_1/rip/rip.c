#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


int ft_strlen(char *s)
{
	int i = 0;
	if (!s)
		return i;
	while (s[i])
		i++;
	return i;
}

// Rets TRUE or FALSE
int check_balanced(char *s)
{
	int ret = 0;
	int i = 0;

	int len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == '(')
			ret++;
		else if(s[i] == ')')
			ret--;
		i++;
	}
	if (ret == 0)
		return 1;
	else
		return 0;
}

void find_min_rem(char *src, int *min_rem, int pos, int curr_rem)
{
	if (curr_rem > *min_rem)
		return;

	if (check_balanced(src))
	{
		if (curr_rem < *min_rem)
			*min_rem = curr_rem;
		return;
	}
	
	int i = pos;
	char saved;
	while (src[i])
	{
		if (src[i] == '(' || src[i] == ')')
		{
			saved = src[i];
			src[i] = ' '; // Quitar parentesis
			find_min_rem(src, min_rem, i + 1, curr_rem + 1); // Probar
			src[i] = saved; // Undo changes
		}
		i++;
	}
}

void rip_recursive(char *src, int min_rem, int pos, int curr_rem)
{
	if (curr_rem > min_rem)
		return;

	if (check_balanced(src) && curr_rem == min_rem)
	{
		puts(src);
		return;
	}

	int i = pos;
	char saved;
	while (src[i])
	{
		if (src[i] == '(' || src[i] == ')')
		{
			saved = src[i];
			src[i] = ' '; // Quitar parentesis
			rip_recursive(src, min_rem, i + 1, curr_rem + 1); // Probar
			src[i] = saved; // Undo changes
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	char *str = argv[1];

	//check que solo tiene paréntesis
	int i = 0;
	while (str[i])
	{
		if (str[i] != '(' && str[i] != ')')
			return 1;
		i++;
	}

	int min_rem = ft_strlen(str);
	find_min_rem(str, &min_rem, 0, 0);
	// printf("min_rem = %i\n", min_rem);

	rip_recursive(str, min_rem, 0, 0);

	return 0;
}