#include "get_next_line.h"

/*
 * ft_strchr MOD
 * ft_memcpy va al revés, de delante atrás
 * ft_strlen MOD
 * ft_memmove MIRÉ; MOD
*/

/*
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	char *str;
	int fd;
	int i = 1;

	fd = open("../prueba.txt", O_RDONLY);
	if (fd < 0)
		return 1;
	while (i <= 20)
	{
		printf("run i = %i------------------\n", i);
		str = get_next_line(fd);
		printf("%s", str);
		printf("---------------END_OF_RUN\n");
		free(str);
		i++;
	}
	return 0;
}
*/

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
		// ((char *)dest)[n - 1] = ((char *)src)[n - 1];
	}
	return dest;
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;

	if (!dest || !src)
		return NULL;
	if (dest > src)
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[n - 1 - i] = ((char *)src)[n - 1 - i];
			i++;
		}
	}
	else if (dest < src)
		return ft_memcpy(dest, src, n);
	else // pq dest == src
		return dest;
	// size_t i = ft_strlen((char *)src) - 1;
	// while (i >= 0)
	// {
	// 	((char *)dest)[i] = ((char *)src)[i];
	// 	i--;
	// }
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

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp;
	int read_ret;

	// while(!tmp)
	// {
	// 	if (!str_append_str(&ret, b))
	// 		return (NULL);
	// 	int read_ret = read(fd, b, BUFFER_SIZE);
	// 	if (read_ret == -1)
	// 		return (NULL);
	// 	b[read_ret] = 0;
	// }
	// if (!str_append_mem(&ret, b, tmp - b + 1))
	// {
	// 	free(ret);
	// 	return NULL;
	// }
	// return ret;

	// check cosas

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	while (1)
	{
		tmp = ft_strchr(b, '\n');
		// si teníamos algo en buffer con \n
		if (tmp)
		{
			if (!str_append_mem(&ret, b, tmp - b + 1))
			{
				if (ret)
					free(ret);
				return NULL;
			}
			ft_memmove(b, tmp + 1, (ft_strlen(tmp + 1) + 1));
			return ret;
		}
		// si no teníamos nada en b con \n, lo añadimos a ret (podría estar vacío pero no pasa nada)
		if (!str_append_str(&ret, b))
			return NULL;
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret <= 0) // o algo mal o readret==0
		{
			b[0] = '\0';
			if (ret && *ret) //si seguimos teniendo cosas en ret, lo devolvemos
				return ret;
			//if (ret) // creo que no hace falta, pq aunque b y ret fuesen NULL, hemos hecho str_append_str y ahora ret no es NULL
			free(ret);
			return NULL;
		}
		b[read_ret] = '\0';
	}
}