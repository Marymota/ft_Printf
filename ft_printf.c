# include "ft_printf.h"

/* FROMATTED OUTPUT FUNCTION 

The printf function prints the optional argument 
under the control of the template string 'format' 
to the stream stdout.
It returns the number of characters printed, or a 
negative value if there was an outpur error

printf() is called with a "format string" that specifies how to format the values of the remaining arguments. 


*/

//	*** INIT VARIABLES ***
//	Iniciate variables that are used 
//	globally to their 'default' values
void init(t_flags *flag)
{
	flag->width = 0;
	flag->left_align = 0;
	flag->asterisk = 0;
	flag->precision = -1;
}

/*	*** PRINTS ***
	Prints individual characters	*/
int ft_putchr(char c)
{
	return (write(1, &c, 1));
}
	
/*	Prints spaces to align content based on 
	width, precision & alignement	*/
void align(int len)
{
	while (len--)
		ft_putchr(' ');
}

/*	Measures the length of a string	*/
int ft_strlen(const char *str)
{
	int	len;

	len = 0; 
	while(*str++)
		++len;
	return(len);
}

/*	Prints an entire string	*/
int ft_putstr(char *str)
{
	int		len;

	len = ft_strlen(str);
	while (*str)
	{
		if (*str && *str != '\0')
			ft_putchr(*str++);
	}
	return (len);
}

int pft_print_prec(char *arg, t_flags *flag, int size)
{
	int idx;

	idx = 0;
	if (flag->width == 0)
		idx = ft_putstr(arg);
	else if (flag->left_align == 0)
	{
		if (size > 0)
			align(size);
		idx = ft_putstr(arg);
	}
	else  if (flag->left_align == 1)
	{
		idx = ft_putstr(arg);
		if (size > 0)
			align(size);
	}
	return (idx);
}

int pft_truncate(char *arg, t_flags *flag)
{
	int idx;
	int count_precision;
	int precision;
	int width;
	
	idx = 0;
	count_precision = flag->precision;
	precision = flag->precision;
	width = flag->width;
	if (flag->left_align == 0)
	{
		if (width - precision > 0)
			align(width - precision);
		while (count_precision--)
		{
			ft_putchr(*arg++);
			++idx;	
		}
	}
	else if (flag->left_align == 1)
	{
		while (count_precision--)
		{
			ft_putchr(*arg++);
			++idx;	
		}
		if (width - precision > 0)
			align(width - precision);
	}
	return (idx);
}

/*	Prints the extra width after 
subtracting the content length */
int print_width (char *arg, t_flags *flag)
{
	int	i;
	int	len;

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
	int idx;
	int len;
	int precision;
	int width;
	int size;
	
	idx = 0;
	len = ft_strlen(arg);
	precision = flag->precision;
	width = flag->width;
	size = 0;
	/*	If precision is less than the length
	of the string, the string will be truncate */
	if (precision < len)
	{
		idx = pft_truncate(arg, flag);
	}
	else if (precision >= len)
	{
		if (precision < width)
		{
			size = width - len;
			idx = pft_print_prec(arg, flag, size);
		}
		else if (precision >= width)
		{
			size = precision - len;
			idx = pft_print_prec(arg, flag, size);
		}
		else if (precision == 0)
			align(width);
	}
	return (idx);
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

/*/
int main (void)
{

}
/*/