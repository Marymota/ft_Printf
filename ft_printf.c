# include "ft_printf.h"

/* FROMATTED OUTPUT FUNCTION 

The printf function prints the optional argument 
under the control of the template string 'format' 
to the stream stdout.
It returns the number of characters printed, or a 
negative value if there was an outpur error

printf() is called with a "format string" that specifies how to format the values of the remaining arguments. 


*/
//PRINTS
//PRINTS / CHAR
int ft_putchr(va_list args)
{
	int c;

	c = va_arg(args, int);
	return (write(1, &c, 1));
}

void align(int idx, int w)
{
	idx = w;
	while (--idx)
		write(1, " ", 1);
}

//PRINTS / STR

int ft_strlen(const char *str)
{
	int i;

	i = 0; 
	while(*str++)
		++i;
	return(i);
}

int ft_putstr(char *str)
{
	char *ptr;
	int i;

	ptr = str;
	while (*ptr)
	{
		if (*ptr && *ptr != '\0')
		{
			write(1, ptr, 1);
		}
		++ptr;
	}
	i = ft_strlen(str);
	return (i);
}

//PRINTS / PRINT_SPECIFIERS

int printf_c (va_list args, int w, int left_align, int idx)
{
	if (w > 0 && left_align == 0)
	{
		align(idx, w);
	}
	idx = ft_putchr(args);
	if (w > 0 && left_align == 1)
		if (w > 0)
			align(idx, w);
	return (idx);
}

int printf_s (va_list args, int w, int left_align, int idx)
{
	int len;
	char *arg;
	char *aux;

	aux = NULL;
	len = 0;
	arg = va_arg(args, char *);
	aux = arg;
	if (w > 0 && left_align == 0)
	{
		len = ft_strlen(arg);
		w = w - len;
		if (w > 0)
			align(idx, w);
	}
	idx = ft_putstr(aux);
	if (w > 0 && left_align == 1)
	{
		len = ft_strlen(aux);
		w = w - len;
		if (w > 0)
			align(idx, w);
	}
	return (idx);
}



// CHAR %c
int int_size(int i)
{
	int ret;

	ret = 0;
	if (i == 0)
		return 0;
	if (!(i / 10))
	{
		return 1;
	}
	else
	{
		++ret;
	}
	++ret;
	return (ret);
}

int is_digit(const char *format)
{
	return (*format >= 48 && *format <= 57);
}

int get_left(const char *format)
{
	if (*format == '-')
	{
		return (1);
	}
	return (0);
}

int get_asterisk(const char *format)
{
	if (*format == '*')
	{
		return (1);
	}
	return (0);
}

int get_width(const char *format, int asterisk, va_list args)
{
	int w; 

	w = 0;
	if (asterisk == 1)
	{
		asterisk = va_arg(args, int);
		return (asterisk);
	}

	if (is_digit(format))
	{
		while (is_digit(format))
		{
			w = w * 10 + (*format - '0');
			format++;
		}
	}
	return (w);
}

int get_spec(const char *format, va_list args, int w, int left_align)
{
	int idx;
	
	idx = 0;
	if (*format == 'c')
		idx = printf_c(args, w, left_align, idx);
	else if (*format == 's')
	{
		idx = printf_s(args, w, left_align, idx);
	}
	if (w > idx)
	{
		return(w);
	}
	return (idx);
}

int parse_format(const char *format, va_list args, int idx)
{
	int w = 0;
	int left_align = 0;
	int asterisk = 0;

	while (*format)
	{
		if (*format == '%')
		{
			++format;
			while (*format == '-' || *format == '*')
			{
				if (*format == '-')
				{
					left_align = get_left(format);
					++format;
				}	
				else if (*format == '*')
				{
					asterisk = get_asterisk(format);
					++format;
				}
			}
			w = get_width(format, asterisk, args);
			if (w < 0)
			{
				w = w * -1;
				left_align = 1;
			}
			if (asterisk == 0)
				format += int_size(w);
			idx += get_spec(format, args, w, left_align);
			left_align = 0;
			asterisk = 0;
		}
		else
		{
			write(1, format, 1);
			++idx;
		}                
		++format;
		//printf("\ntest: %s\n", format);
	}
	return (idx);
}

int ft_printf(const char *format, ...)
{
	va_list args;
	int done;
	int idx;

	idx = 0;
	va_start(args, format);
	done = parse_format(format, args, idx);

	va_end (args);
	return (done);
}

/*/
int main (void)
{
	printf("\n-----//TEST 1\n-------------------\n");
	printf("\nidx: %i\n", printf("%s", ""));
	printf("\nidx: %i\n", ft_printf("%s", ""));
	printf("\n-----//TEST 2\n-------------------\n");
	printf("\nidx: %i\n", printf("%s", "0"));
	printf("\nidx: %i\n", ft_printf("%s", "0"));
	printf("\n-----//TEST 3\n-------------------\n");
	// Empty values cause over-counting; Add strlen()
	printf("\nidx: %i\n", printf("%s %s", "", ""));
	printf("\nidx: %i\n", ft_printf("%s %s", "", ""));
	printf("\n-----//TEST 4\n-------------------\n");
	printf("\nidx: %i\n", printf("%s %s", "0", "1"));
	printf("\nidx: %i\n", ft_printf("%s %s", "0", "1"));
	printf("\n-----//TEST 5\n-------------------\n");
	printf("\nidx: %i\n", printf(" %s %s ", "0", "1"));
	printf("\nidx: %i\n", ft_printf(" %s %s ", "0", "1"));
	printf("\n-----//TEST 6\n-------------------\n");
	printf("\nidx: %i\n", printf(" %s %s ", "", ""));
	printf("\nidx: %i\n", ft_printf(" %s %s ", "", ""));
	printf("\n-----//TEST 7\n-------------------\n");
	printf("\nidx: %i\n", printf(" %1s %1s ", "123", "4567"));
	printf("\nidx: %i\n", ft_printf(" %1s %1s ", "123", "4567"));
	printf("\n-----//TEST 8\n-------------------\n");
	printf("\nidx: %i\n", printf(" %4s %4s ", "123", "4567"));
	printf("\nidx: %i\n", ft_printf(" %4s %4s ", "123", "4567"));
	printf("\n-----//TEST 9\n-------------------\n");
	printf("\nidx: %i\n", printf(" %-4s %4s ", "123", "4567"));
	printf("\nidx: %i\n", ft_printf(" %-4s %4s ", "123", "4567"));
	printf("\n-----//TEST 10\n-------------------\n");
	printf("\nidx: %i\n", printf(" %4s %-4s", "123", "4567"));
	printf("\nidx: %i\n", ft_printf(" %4s %-4s", "123", "4567"));
	printf("\n-----//TEST 11\n-------------------\n");
	printf("\nidx: %i\n", printf(" %-4s %-4s", "123", "4567"));
	printf("\nidx: %i\n", ft_printf(" %-4s %-4s", "123", "4567"));
	
}
/*/