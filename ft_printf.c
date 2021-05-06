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
int ft_putchr(char c)
{
	return (write(1, &c, 1));
}

void align(int w)
{
	int i;

	i = w;
	while (--i)
		ft_putchr(' ');
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

 	i = 0;
	ptr = str;
	while (*ptr)
	{
		if (*ptr && *ptr != '\0')
		{
			ft_putchr(*ptr);
		}
		++ptr;
	}
	i += ft_strlen(str);
	return (i);
}

//PRINTS / PRINT_SPECIFIERS

int printf_c (va_list args, t_flags *flag, int idx)
{
	int arg;

	arg = va_arg(args, int);
	
	if (flag->width > 0 && flag->left_align == 0)
		align(flag->width);
	idx = ft_putchr(arg);
	if (flag->width > 0 && flag->left_align == 1)
		align(flag->width);
	return (idx);
}

int printf_s (va_list args, t_flags *flag, int idx)
{
	int len;
	char *arg;
	int aux;

	aux = 0;
	len = 0;
	arg = va_arg(args, char *);

	if (flag->width > 0 && flag->left_align == 0)
	{
		len = ft_strlen(arg);
		flag->width = (flag->width + 1) - len;
		if (flag->width > 0)
		{
			aux += flag->width - 1;
			align(flag->width);
		}
	}
	idx = ft_putstr(arg);
	if (flag->width > 0 && flag->left_align == 1)
	{
		len = ft_strlen(arg);
		flag->width = (flag->width + 1) - len;
		if (flag->width > 0)
		{
			aux += flag->width - 1;
			align(flag->width);
		}
	}
	return (idx + aux);
}

// CHAR %c
int int_size(int i)
{
	int ret;

	ret = 0;
	if (i == 0)
		return 0;
	if (!(i / 10))
		return 1;
	else
		++ret;
	++ret;
	return (ret);
}


//CHECKS
int is_digit(const char *format)
{
	return (*format >= 48 && *format <= 57);
}

int check_left(const char *format)
{
	if (*format == '-')
	{
		return (1);
	}
	return (0);
}

int check_asterisk(const char *format)
{
	if (*format == '*')
	{
		return (1);
	}
	return (0);
}

int check_precision(const char *format)
{
	if (*format == '.')
	{
		return (1);
	}
	return (0);
}

int get_width(const char *format, t_flags *flag, va_list args)
{
	flag->width = 0;
	if (flag->asterisk == 1)
	{
		flag->asterisk = va_arg(args, int);
		return (flag->asterisk);
	}

	if (is_digit(format))
	{
		while (is_digit(format))
		{
			flag->width = flag->width * 10 + (*format - '0');
			format++;
		}
	}
	return (flag->width);
}

int get_spec(const char *format, va_list args, t_flags *flag)
{
	int idx;
	
	idx = 0;
	if (*format == 'c')
		idx = printf_c(args, flag, idx);
	else if (*format == 's')
	{
		idx = printf_s(args, flag, idx);
	}
	if (flag->width > idx)
	{
		return(flag->width);
	}
	return (idx);
}

int parse_format(const char *format, va_list args, t_flags *flag, int idx)
{
	flag->width = 0;
	flag->left_align = 0;
	flag->asterisk = 0;
	flag->precision = 0;

	while (*format)
	{
		if (*format == '%')
		{
			++format;
			while (*format == '-' || *format == '*' || *format == '.')
			{
				if (*format == '-')
				{
					flag->left_align = check_left(format);
					++format;
				}	
				else if (*format == '*')
				{
					flag->asterisk = check_asterisk(format);
					++format;
				}
				else if (*format == '.')
				{
					flag->precision = check_precision(format);
					++format;
				}
			}
			flag->width = get_width(format, flag, args);
			if (flag->width < 0)
			{
				flag->width = flag->width * -1;
				flag->left_align = 1;
			}
			if (flag->asterisk == 0)
				format += int_size(flag->width);
			idx += get_spec(format, args, flag);
			flag->left_align = 0;
			flag->asterisk = 0;
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

int ft_printf(const char *format, ...)
{
	va_list args;
	t_flags flag;
	int done;
	int idx;

	idx = 0;
	va_start(args, format);
	done = parse_format(format, args, &flag, idx);

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
	intf("\n-----//TEST 7\n-------------------\n");
	intf("\nidx: %i\n", printf("%1s%1s", "123", "4567"));
	intf("\nidx: %i\n", ft_printf("%1s%1s", "123", "4567"));
	intf("\n-----//TEST 8\n-------------------\n");
	intf("\nidx: %i\n", printf("%4s%4s", "123", "4567"));
	intf("\nidx: %i\n", ft_printf("%4s%4s", "123", "4567"));
	printf("\n-----//TEST 9\n-------------------\n");
	printf("\nidx: %i\n", printf(" %-4s %4s ", "123", "4567"));
	printf("\nidx: %i\n", ft_printf(" %-4s %4s ", "123", "4567"));
	printf("\n-----//TEST 10\n-------------------\n");
	printf("\nidx: %i\n", printf(" %4s %-4s", "123", "4567"));
	printf("\nidx: %i\n", ft_printf(" %4s %-4s", "123", "4567"));
	printf("\n-----//TEST 11\n-------------------\n");
	printf("\nidx: %i\n", printf(" %-4s %-4s", "123", "4567"));
	printf("\nidx: %i\n", ft_printf(" %-4s %-4s", "123", "4567"));
	//printf("\n-----//TEST 16\n-------------------\n");
	//printf("\nidx: %i\n", printf(" %*.s %.1s ", 10, "123", "4567"));
	//printf("\nidx: %i\n", ft_printf(" %*.s %.1s ", 10, "123", "4567"));
}
/*/