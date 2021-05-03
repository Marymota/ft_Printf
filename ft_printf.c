# include "printf.h"

/* FROMATTED OUTPUT FUNCTION 

The printf function prints the optional argument 
under the control of the template string 'format' 
to the stream stdout.
It returns the number of characters printed, or a 
negative value if there was an outpur error

printf() is called with a "format string" that specifies how to format the values of the remaining arguments. 


*/
int int_size(int i)
{
	int ret;

	ret = 0;
	if (!(i / 10))
	{
		return 0;
	}
	else
	{
		++ret;
	}
	++ret;
	return (ret);
}

int is_digit(char *format)
{
	return (*format >= 48 && *format <= 57);
}

int ft_putchr(va_list args)
{
	int c;

	c = va_arg(args, int);
	return (write(1, &c, 1));
}

int get_width(char *format)
{
	int w; 

	w = 0;
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

int get_spec(char *format, va_list args, int idx, int w)
{
	if (w > 0)
	{
		idx = w;
		while (--idx)
		{
			write(1, " ", 1);
		}
	}
	if (*format == 'c')
	{
		idx = ft_putchr(args);
	}
	if (w > idx)
	{
		return(w);
	}
	return (idx);
}

int parse_format(char *format, va_list args, int idx)
{
	int w; 

	w = 0;

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			w = get_width(format);
			format += int_size(w);
			idx += get_spec(format, args, idx, w);
		}
		else
		{
			write(1, format, 1);
			++idx;
		}                
		++format;
	}
	return (idx);
}

int ft_printf(char *format, ...)
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

int main (void)
{
	printf("\n-------------//TEST 1\n------------------------\n");
	printf("\nidx: %i\n", printf("%c", '0'));
	printf("\nidx: %i\n", ft_printf("%c", '0'));
	printf("\n-------------//TEST 2\n------------------------\n");
	printf("\nidx: %i\n", printf("%c ", '0'));
	printf("\nidx: %i\n", ft_printf("%c ", '0'));
	printf("\n-------------//TEST 3\n------------------------\n");
	printf("\nidx: %i\n", printf("10%c", '0'));
	printf("\nidx: %i\n", ft_printf("10%c", '0'));
	printf("\n-------------//TEST 4\n------------------------\n");
	printf("\nidx: %i\n", printf("%10c", '0'));
	printf("\nidx: %i\n", ft_printf("%10c", '0'));
	printf("\n-------------//TEST 5\n------------------------\n");
	printf("\nidx: %i\n", printf("%10c", '0'));
	printf("\nidx: %i\n", ft_printf("%10c", '0'));
	printf("\n-------------//TEST 6\n------------------------\n");
	printf("\nidx: %i\n", printf("%-10c", '0'));
	printf("\nidx: %i\n", ft_printf("%-10c", '0'));
}