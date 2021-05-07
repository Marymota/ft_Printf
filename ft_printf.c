# include "ft_printf.h"

/* FROMATTED OUTPUT FUNCTION 

The printf function prints the optional argument 
under the control of the template string 'format' 
to the stream stdout.
It returns the number of characters printed, or a 
negative value if there was an outpur error

printf() is called with a "format string" that specifies how to format the values of the remaining arguments. 


*/

//INIT VARIABLES
void init(t_flags *flag)
{
	flag->width = 0;
	flag->left_align = 0;
	flag->asterisk = 0;
	flag->precision = -1;
}

//PRINTS
//PRINTS / CHAR
int ft_putchr(char c)
{
	return (write(1, &c, 1));
}

void align(int w)
{
	while (w--)
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

	int print_width (char *arg, t_flags *flag)
	{
		int i;
		int len;

		i = 0;
		len = ft_strlen(arg);
		flag->width = flag->width - len;
		if (flag->width > 0)
		{
			i = flag->width;
			align(flag->width);
		}
		return (i);
	}

	int print_precision (char *arg, t_flags *flag)
	{
		int len = ft_strlen(arg);
		int i;

		
		i = 0;
		//printf("\ntest: %s %i\n", arg, flag->precision);
		if (flag->precision == 0)
			align(flag->width);
		else if (flag->precision == len)
		{
			if (flag->width - len > 0)
				align(flag->width - len);
			i = ft_putstr(arg);
		}
		else if (flag->precision > len)
		{
			if (flag->width - len > 0)
				align(flag->width - len);
			i = ft_putstr(arg);
		}
		else
		{
			while (flag->precision--)
			{
				ft_putchr(*arg++);
				i++;
			}
		}
		return (i);
	}

//PRINTS / PRINT_SPECIFIERS

int printf_c (va_list args, t_flags *flag, int idx)
{
	int arg;

	arg = va_arg(args, int);
	
	if (flag->width > 1 && flag->left_align == 0)
		align(flag->width - 1);
	idx = ft_putchr(arg);
	if (flag->width > 1 && flag->left_align == 1)
		align(flag->width - 1);
	return (idx);
}

int printf_s (va_list args, t_flags *flag, int idx)
{
	char *arg;
	int aux = 0;
	//int len = 0;

	arg = va_arg(args, char *);

	if (flag->precision >= 0)
	{
		//printf("\ntest: %i\n", aux);
		aux += print_precision(arg, flag);
	}
	else 
	{
		if (flag->width > 0 && flag->left_align == 0)
			aux += print_width(arg, flag);
		idx = ft_putstr(arg);
		if (flag->width > 0 && flag->left_align == 1)
			aux += print_width(arg, flag);
	}
	return (idx + aux);
}

// CHAR %c
int int_size(int i)
{
	int ret;

	ret = 0;
	if (i == 0)
		return 1; //If it returns 0 it can't advance when the digit is '0'
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
		return (0);
	}
	return (-1);
}

int count_width(const char *format, t_flags *flag, va_list args)
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

int count_precision(const char *format, t_flags *flag, va_list args)
{
	flag->precision = 0;
	if (flag->asterisk == 1)
	{
		flag->asterisk = va_arg(args, int);
		return (flag->asterisk);
	}
	if (is_digit(format))
	{
		while (is_digit(format))
		{
			flag->precision = flag->precision * 10 + (*format - '0');
			//printf("\ntest: %i \n", flag->precision);
			++format;
		}
	}
	//printf("\ntest: %i \n", flag->precision);
	return (flag->precision);
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
	init(flag);
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			while (*format == '-' || *format == '*' || *format == '.' || is_digit(format))
			{
				if (*format == '-')
				{
					flag->left_align = check_left(format);
					++format;
				}	
				else if (*format == '*')
				{
					flag->asterisk = check_asterisk(format);
					
					if (flag->precision >= 0) // If default value is negative don't forget to compare...
						flag->precision = count_width(format, flag, args);
					else
					{
						flag->width = count_width(format, flag, args);
						flag->asterisk = 0;
						
					}
					if (flag->width < 0)
					{
						flag->width = flag->width * -1;
						flag->left_align = 1;
					}
					++format;
				}
				else if (is_digit(format))
				{
					if (flag->precision >= 0) // If default value is negative don't forget to compare...
					{
						flag->precision = count_precision(format, flag, args);
						if (flag->precision < 0)
						{
							flag->precision = flag->precision * -1;
							flag->left_align = 1;
						}
						format += int_size(flag->precision);
					}
					else 
					{
						flag->width = count_width(format, flag, args);
						if (flag->width < 0)
						{
							flag->width = flag->width * -1;
							flag->left_align = 1;
						}
						format += int_size(flag->width);
					}

				}
				else if (*format == '.')
				{
					flag->precision = check_precision(format);
					++format;
					//flag->precision = count_precision(format, flag, args);
					//printf("\ntest: %i %s \n", flag->precision, format);
				}
			}
			idx += get_spec(format, args, flag);
			init(flag);
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

//
int main (void)
{
	//%C
	//printf("\n-----//TEST 4\n-------------------\n");
	//printf("\nidx: %i\n", printf("%10c", '0'));
	//printf("\nidx: %i\n", ft_printf("%10c", '0'));

	//printf("\n-----//TEST 8\n-------------------\n");
	//printf("\nidx: %i\n", printf("%*c", 1, '0'));
	//printf("\nidx: %i\n", ft_printf("%*c", 1, '0'));
//
	//printf("\n-----//TEST 11\n-------------------\n");
	//printf("\nidx: %i\n", printf("%*c", -2, '0'));
	//printf("\nidx: %i\n", ft_printf("%*c", -2, '0'));
//
	//printf("\n-----//TEST 17\n-------------------\n");
	//printf("\nidx: %i\n", printf("%*c%c*", -10, '0', 1));
	//printf("\nidx: %i\n", ft_printf("%*c%c*", -10, '0', 1));

	//%S
	//printf("\n-----//TEST 1\n-------------------\n");
	//printf("\nidx: %i\n", printf("%s", ""));
	//printf("\nidx: %i\n", ft_printf("%s", ""));
	//printf("\n-----//TEST 2\n-------------------\n");
	//printf("\nidx: %i\n", printf("%s", "0"));
	//printf("\nidx: %i\n", ft_printf("%s", "0"));
	//printf("\n-----//TEST 3\n-------------------\n");
	//// Empty values cause over-counting; Add strlen()
	//printf("\nidx: %i\n", printf("%s %s", "", ""));
	//printf("\nidx: %i\n", ft_printf("%s %s", "", ""));
	//printf("\n-----//TEST 4\n-------------------\n");
	//printf("\nidx: %i\n", printf("%s %s", "0", "1"));
	//printf("\nidx: %i\n", ft_printf("%s %s", "0", "1"));
	//printf("\n-----//TEST 5\n-------------------\n");
	//printf("\nidx: %i\n", printf(" %s %s ", "0", "1"));
	//printf("\nidx: %i\n", ft_printf(" %s %s ", "0", "1"));
	//printf("\n-----//TEST 6\n-------------------\n");
	//printf("\nidx: %i\n", printf(" %s %s ", "", ""));
	//printf("\nidx: %i\n", ft_printf(" %s %s ", "", ""));
	//printf("\n-----//TEST 7\n-------------------\n");
	//printf("\nidx: %i\n", printf("%1s%1s", "123", "4567"));
	//printf("\nidx: %i\n", ft_printf("%1s%1s", "123", "4567"));
	//printf("\n-----//TEST 8\n-------------------\n");
	//printf("\nidx: %i\n", printf("%4s%4s", "123", "4567"));
	//printf("\nidx: %i\n", ft_printf("%4s%4s", "123", "4567"));
	//printf("\n-----//TEST 9\n-------------------\n");
	//printf("\nidx: %i\n", printf(" %-4s %4s ", "123", "4567"));
	//printf("\nidx: %i\n", ft_printf(" %-4s %4s ", "123", "4567"));
	//printf("\n-----//TEST 10\n-------------------\n");
	//printf("\nidx: %i\n", printf(" %4s %-4s", "123", "4567"));
	//printf("\nidx: %i\n", ft_printf(" %4s %-4s", "123", "4567"));
	//printf("\n-----//TEST 11\n-------------------\n");
	//printf("\nidx: %i\n", printf(" %-4s %-4s", "123", "4567"));
	//printf("\nidx: %i\n", ft_printf(" %-4s %-4s", "123", "4567"));
	//printf("\n-----//TEST 13\n-------------------\n");
	//printf("\nidx: %i\n", printf("%*s%*s", 1, "123", 10, "4567"));
	//printf("\nidx: %i\n", ft_printf("%*s%*s", 1, "123", 10, "4567"));
	//printf("\n-----//TEST 16\n-------------------\n");
	//printf("\nidx: %i\n", printf("%*.s%.1s", 10, "123", "4567"));
	//printf("\nidx: %i\n", ft_printf("%*.s%.1s", 10, "123", "4567"));
	printf("\n-----//TEST 17\n-------------------\n");
	printf("\nidx: %i\n", printf("%*.0s%.2s", 10, "123", "4567"));
	printf("\nidx: %i\n", ft_printf("%*.0s%.2s", 10, "123", "4567"));
	printf("\n-----//TEST 18\n-------------------\n");
	printf("\nidx: %i\n", printf("%*.3s%.3s", 10, "123", "4567"));
	printf("\nidx: %i\n", ft_printf("%*.3s%.3s", 10, "123", "4567"));
	printf("\n-----//TEST 19\n-------------------\n");
	printf("\nidx: %i\n", printf("%*.4s%.4s", 10, "123", "4567"));
	printf("\nidx: %i\n", ft_printf("%*.4s%.4s", 10, "123", "4567"));
	printf("\n-----//TEST 22\n-------------------\n");
	printf("\nidx: %i\n", printf("%*.5s%*.5s", -10, "123", 10, "4567"));
	printf("\nidx: %i\n", ft_printf("%*.5s%*.5s", -10, "123", 10, "4567"));
}
//