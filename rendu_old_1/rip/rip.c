#include "rip.h"

/*
 * allowed functs: puts; write
 * rip debe print todas las combinaciones de parentesis
 * sustituyendo '(' o ')' por ' ' (espacio)
*/

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	if (!argv || !argv[0])
		return 1;
	if (argc != 2)
		return 1;
	char *input = argv[1];
	printf("input: %s\n", input);

	rip(input, 0);

	return 0;
}



void rip(char *str, size_t pos)
{
	
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