#include "get_next_line.h"


/*
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	char *str;
	int fd;
	int i = 1;

	fd = open("../empty", O_RDONLY); // prueba.txt
	if (fd < 0)
		return 1;
	while (i <= 20)
	{
		printf("i = %i ----------------------\n", i);
		str = get_next_line(fd);
		printf("%s", str);
		printf("-----------------end-of-ret\n");
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


char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp;
	int readret;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	while (1)
	{
		tmp = ft_strchr(b, '\n');
		if (tmp)
		{
			if (!str_append_mem(&ret, b, tmp - b + 1))
			{
				if (ret)
					free(ret);
				return NULL;
			}
			ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
			return ret;
		}
		if (!str_append_str(&ret, b))
			return NULL;
		readret = read(fd, b, BUFFER_SIZE);
		if (readret <= 0)
		{
			b[0]='\0';
			if (ret && *ret)
				return ret;
			free(ret);
			return NULL;
		}
		b[readret] = '\0';
	}
}