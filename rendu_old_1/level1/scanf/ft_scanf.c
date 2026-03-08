#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

/*
 * Allowed functions:
 * stdin, isspace, isdigit,
 * fgetc, ungetc, ferror, feof,
 * va_start, va_arg, va_copy, va_end
*/

/**/

// Función para saltar espacios en blanco en el stream
int match_space(FILE *f)
{
	int ch = fgetc(f);
	if (ch == EOF && ferror(f))
		return -1;

	while (ch != EOF)
	{
		if (!isspace(ch))
		{
			ungetc(ch, f);
			break;
		}
		ch = fgetc(f);
	}
    
	if (ferror(f))
		return -1;
	return 1;
}

// Función para verificar un carácter específico
int match_char(FILE *f, char c)
{
	int ch = fgetc(f);
	if (ch == c)
		return 1;
	if (ch != EOF)
		ungetc(ch, f);
    return -1;
}

// Función para leer un carácter (%c)
int scan_char(FILE *f, va_list ap)
{
	int ch = fgetc(f);
	char *cp = va_arg(ap, char *);

	if (ch == EOF)
		return -1;

	*cp = (char)ch;
    return 1;
}

// Función para leer un entero (%d)
int scan_int(FILE *f, va_list ap)
{
    /*
     * CONVERSIÓN %d:
     * - Saltar espacios en blanco iniciales
     * - Leer signo opcional (+/-)
     * - Leer dígitos y construir el número
     * - Devolver último carácter no-dígito al stream
     */
    int sign = 1;
    int value = 0;
    int ch = fgetc(f);
    int *ip = va_arg(ap, int *);
    int count = 0;

    if (ch == EOF)
        return -1;
    
    // Saltar espacios en blanco
    while (isspace(ch))
        ch = fgetc(f);
    
    // Manejar signo
    if (ch == '-')
    {
        sign = -1;
        ch = fgetc(f);
    }
    else if (ch == '+')
    {
        ch = fgetc(f);
    }
    
    // Verificar que el primer carácter sea un dígito
    if (!isdigit(ch))
    {
        ungetc(ch, f);
        return -1;
    }
    
    // Leer dígitos y construir el número
    while (isdigit(ch))
    {
        value = value * 10 + (ch - '0');
        count++;
        ch = fgetc(f);
    }
    
    // Devolver último carácter no-dígito
    if (ch != EOF)
        ungetc(ch, f);

    if (count == 0)
        return -1;
    
    *ip = value * sign;
    return 1;
}

// Función para leer un string (%s)
int scan_string(FILE *f, va_list ap)
{
	int ch = fgetc(f);
	char *sp = va_arg(ap, char *);
	int i = 0;

	// Saltar espacios en blanco iniciales
	while (ch != EOF && isspace(ch))
		ch = fgetc(f);

	if (ch == EOF)
		return -1;

	do
	{
		sp[i] = ch;
		i++;
		ch = fgetc(f);
	} while (ch != EOF && !isspace(ch));
	
	sp[i] = '\0';

	//Devolver caracter del espacio al sist:

	if (ch != EOF)
		ungetc(ch, f);
	
	if (i == 0)
		return -1;
	return 1;
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case '\0':
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else
		{
			if (match_char(f, *format) != 1)
				break;
		}
		format++;
	}
	
	if (ferror(f))
		return EOF;

	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);

	return ret;
}

/* 
EJEMPLO DE USO:
*/
// int main(void)
// {
//     char x1;
// 	// char x2;
//     char str[100];
//     // int i;

//     // Leer: número, espacio, string, espacio, carácter
//     int converted = ft_scanf("%c %s", &x1, str);
    
//     printf("Convertidos: %d\n", converted);
//     printf("Números: , String: %s, Carácter: 1: %c\n", str, x1);
    
//     return 0;
// }
