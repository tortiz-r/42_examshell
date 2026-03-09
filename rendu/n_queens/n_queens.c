# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

/*
 * allowed functs:
 * atoi, fprintf, write, calloc, malloc, free, realloc, stdout, stderr
 * 
 * output format: p1 p2 p3 ... p == line index of queen in col i
*/

int is_digit(char *str)
{
	int i = 0;

	if (!str)
		return 0;

	if (i < ft_strlen(str))
	{
		if (str[i] < '0' && str[i] > '9')
			return 0;
		i++;
	}
	return 0;
}

print_sol(int num, int *queens)
{
	int i = 0;

	if (num == 0)
		return;

	fprintf(stdout, "%i", queens[i]);
	i++;
	while (i < num)
	{
		fprintf(stdout, ", %i", queens[i]);
	}
	fprintf(stdout, "\n");
}


int is_valid_pos(int num, int *queens, int x, int y);

int is_valid_sol(int num, int *queens)
{
	int i = 0;
	int valid = 1;

	if (!queens)
		return 0;

	while (i < num && valid)
	{
		if (is_valid_pos(num, queens, i, queens[i]))
			valid = 1;
		else
			valid = 0;
		i++;
	}
	return valid;
}

void gen_queens(int num, int *queens, int act_size, int pos)
{
	// Base case

	if (pos == num)
	{
		if (is_valid_sol(num, queens))
			print_sol(num, queens);	
		if (queens)
				free(queens);
		return;
	}

	int try_y = 1;
	int *new_queens;

	while (try_y <= num)
	{
		if (is_valid_pos(num, queens, pos, try_y))
		{
			new_queens = cpy_queens(num, queens);
			if (!new_queens)
				return;
			new_queens[pos] = try_y;
			gen_queens();
		}
		// algo mas por aqui
	}
	new_queens = calloc(num, sizeof(int));
	if (!queens)
		return 1;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	
	char str = argv[1];
	if (!is_digit(str))
		return 1;
	
	int num = atoi(str);
	if (num == 1 || num == 2)
		return 0;

	gen_queens(num, NULL, 0, 0);

	return 0;
}