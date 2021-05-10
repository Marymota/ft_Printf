# include "ft_printf.h"

/* FROMATTED OUTPUT FUNCTION 

The printf function prints the optional argument 
under the control of the template string 'format' 
to the stream stdout.
It returns the number of characters printed, or a 
negative value if there was an outpur error

printf() is called with a "format string" that specifies how to format the values of the remaining arguments. 

*/




//	*** LIBFT Functions ***
/*	Prints a singular character	*/
int ft_putchr(char c)
{
	return (write(1, &c, 1));
}
/*	Prints a number	*/
void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putchr('-');
		ft_putchr('2');
		ft_putnbr(147483648);
	}
	else if (n < 0)
	{
		ft_putchr('-');
		ft_putnbr(n * -1);
	}
	else if (n / 10)
	{
		ft_putnbr(n / 10);
		ft_putchr(n % 10 + '0');
	}
	else
		ft_putchr(n + '0');
}
/*	Prints spaces to align content based on width, precision & alignement	*/
void	align(int len)
{
	while (len--)
		ft_putchr(' ');
}
/*	Checks is a character is a digit*/
int is_digit(const char *format)
{
	return (*format >= 48 && *format <= 57);
}
/*	Counts digits of numeric values*/
int int_size(int i)
{
	int idx;

	idx = 0;
	if (i == 0)
		return 1;
	if (!(i / 10))
		return 1;
	else
		++idx;
	++idx;
	return (idx);
}

/*	Counts digits/chars of hexadecimal values	*/
int count_hex(unsigned long n)
{
	int idx;

	idx = 0;
	while (n > 0)
	{
		n = n / 16;
		++idx;
	}	
	return (idx);
}
/*	Returns a number from a combination of digit characters	*/
int count_width(const char *format, va_list args, t_flags *flag)
{
	int ret;

	ret = 0;
	if (flag->asterisk == 1)
	{
		flag->asterisk = va_arg(args, int);
		return (flag->asterisk);
	}
	if (is_digit(format))
	{
		while (is_digit(format))
		{
			ret = ret * 10 + (*format - '0');
			++format;
		}
	}
	return (ret);
}
/*	Advances format after counting width and/or precision	*/
int count_digits(const char *format, va_list args, t_flags *flag)
{
	int fmt;

	fmt = 0;
	if (flag->precision >= 0) // If default value is negative don't forget to compare...
	{
		flag->precision = count_width(format, args, flag);
		fmt =int_size(flag->precision);
	}
	else 
	{
		flag->width = count_width(format, args, flag);
		fmt = int_size(flag->width);
	}
	return (fmt);
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
/*	Prints the hexadecimal value referent to an address*/
int ft_putaddr(unsigned long n, int idx)
{

	idx = count_hex(n);
	if (n > 15)
	{
		ft_putaddr((n / 16), idx);
		ft_putaddr((n % 16), idx);
	}
	else if (n < 10)
	{
		ft_putchr(n + '0');
	}
	else 
	{
		if (n == 10)
			ft_putchr('a');
		else if (n == 11)
			ft_putchr('b');
		else if (n == 12)
			ft_putchr('c');
		else if (n == 13)
			ft_putchr('d');
		else if (n == 14)
			ft_putchr('e');
		else if (n == 15)
			ft_putchr('f');
	}
	//printf("\ntest: %li\n", aux);
	return (idx);
}

//	*** PRINT_PARSE FLAGS	***
/*	If precision is less than the length of the string, the string will be truncate */
int printf_truncate(char *arg, t_flags *flag)
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
/*	Prints the extra width after subtracting the content length */
int printf_precision(char *arg, t_flags *flag, int size)
{
	int	idx;

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
/*	Prints the extra width after subtracting the content length */
int parse_width (char *arg, t_flags *flag)
{
	int	idx;
	int	len;

	idx = 0;
	len = ft_strlen(arg);
	flag->width = flag->width - len;
	if (flag->width > 0)
	{
		idx = flag->width;
		align(flag->width);
	}
	return (idx);
}
/*	Returns the necessary extra width space when precision is used*/
int parse_precision (char *arg, t_flags *flag)
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
	if (precision < len)
		idx = printf_truncate(arg, flag);
	else if (precision >= len)
	{
		if (precision < width)
			size = width - len;
		else if (precision >= width)
			size = precision - len;
		else if (precision == 0)
			align(width);
		idx = printf_precision(arg, flag, size);
	}
	return (idx);
}
/*	Prints the extra width after subtracting the content length and '0x'(2) */
int parse_hexadecimal(ssize_t address, t_flags *flag)
{
	int	idx;
	int	len;

	idx = 0;
	len = count_hex(address);
	flag->width = flag->width - len - 2;
	if (flag->width > 0)
	{
		idx = flag->width;
		align(flag->width);
	}
	return (idx);
}


//	PRINT_SPECIFIERS ***
/*	Prints and aligns one character	*/
int printf_c (va_list args, t_flags *flag, int idx)
{
	int	arg;

	arg = va_arg(args, int);
	if (flag->width > 1 && flag->left_align == 0)
		align(flag->width - 1);
	idx = ft_putchr(arg);
	if (flag->width > 1 && flag->left_align == 1)
		align(flag->width - 1);
	return (idx);
}
/*	Processes the printing of strings	*/
int printf_s (va_list args, t_flags *flag, int idx)
{
	char	*arg;

	arg = va_arg(args, char *);
	if (flag->precision >= 0)
		idx += parse_precision(arg, flag);
	else 
	{
		if (flag->width > 0 && flag->left_align == 0)
			idx += parse_width(arg, flag);
		idx += ft_putstr(arg);
		if (flag->width > 0 && flag->left_align == 1)
			idx += parse_width(arg, flag);
	}
	return (idx);
}
/*	Processes the printing pointer addresses	*/
int printf_p (va_list args, t_flags *flag, int idx)
{
	void	*arg;
	ssize_t	address;
		
	arg = va_arg(args, void *);
	address = (ssize_t)(arg);

	if (address != 0)
	{
		if (flag->width > 0 && flag->left_align == 0)
		idx += parse_hexadecimal(address, flag);
		write (1, "0x", 2);
		idx += ft_putaddr(address, idx);
	}
	else
	{
		flag->width -= 3;
		if (flag->width > 0 && flag->left_align == 0)
			idx += parse_hexadecimal(address, flag) + 6;
		write (1, "(nil)", 5);
	}
	if (flag->width > 0 && flag->left_align == 1)
		idx += parse_hexadecimal(address, flag);
	return (idx + 2);
}
/*	Processes the printing of digits	*/
/*int printf_d (va_list args, t_flags *flag, int idx)
{
	void	*arg;
	ssize_t	number;
		
	arg = va_arg(args, void *);
	number = (ssize_t)(arg);

	if (number != 0)
	{
		if (flag->width > 0 && flag->left_align == 0)
		idx += parse_width(number, flag);
		idx += ft_putnbr(number);
	}
	else
	{
		flag->width -= 3;
		if (flag->width > 0 && flag->left_align == 0)
			idx += parse_width(number, flag) + 6;
		idx += ft_putnbr(number);
	}
	if (flag->width > 0 && flag->left_align == 1)
		idx += parse_width(number, flag);
	return (idx + 2);
}
*/


//	*** PARSING FORMAT ***
/*	Finds the specifier and sends it to be print	*/

int get_specifier(const char *format, va_list args, t_flags *flag)
{
	int	idx;
	
	idx = 0;
	if (*format == 'c')
		idx = printf_c(args, flag, idx);
	else if (*format == 's')
		idx = printf_s(args, flag, idx);
	else if (*format == 'p')
		idx = printf_p(args, flag, idx);
	if (flag->width > idx)
	{
		return(flag->width);
	}
	return (idx);
}
/*	Defines the value for precision and width if the asterisk flag is used  */
void parse_asterisk(const char *format, va_list args, t_flags *flag)
{
	if (flag->precision >= 0) // If default value is negative don't forget to compare...
		flag->precision = count_width(format, args, flag);
	else
	{
		flag->width = count_width(format, args, flag);
		flag->asterisk = 0;
	}
	if (flag->width < 0)
	{
		flag->width = flag->width * -1;
		flag->left_align = 1;
	}
}
/*	Find and update flags value 	*/
int get_flags(const char *format, va_list args, t_flags *flag)
{
	if (*format == '-')
		flag->left_align = 1;
	else if (*format == '*')
	{
		flag->asterisk = 1;
		parse_asterisk(format, args, flag);
	}
	else if (*format == '.')
		flag->precision = 0;
	else	
		return (0);
	return (1);
}
/*	Iniciate variables that are used globally to their 'default' values */
void init(t_flags *flag)
{
	flag->width = 0;
	flag->left_align = 0;
	flag->asterisk = 0;
	flag->precision = -1;
}
/*	Parse the format string to find flags width, precision & specifier	*/
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
				if (get_flags(format, args, flag))
					++format;
				else if (is_digit(format))
					format += count_digits(format, args, flag);
			}
			idx += get_specifier(format, args, flag);
			init(flag);
		}
		else
		{
			idx += ft_putchr(*format);
		}                
		++format;
	}
	return (idx);
}
/*	Iniciates a list of variadic arguments and sends the format string to be parsed*/
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
	int G = -1;
	//static int s;
	//int a;
	//int *p;
//
	//p = malloc(sizeof(int));

	//printf("\n-----//TEST 1\n-------------------\n");
	printf("  idx: %i\n\n", printf("%p", (void *) &G));
	printf("  idx: %i\n\n", ft_printf("%p", (void *) &G));
	//printf("idx: %i\n\n", printf("&s    = %p\n", (void *) &s));
	//printf("idx: %i\n\n", ft_printf("&s    = %p\n", (void *) &s));
	//printf("idx: %i\n\n", printf("&a    = %p\n", (void *) &a));
	//printf("idx: %i\n\n", ft_printf("&a    = %p\n", (void *) &a));
	//printf("idx: %i\n\n", printf("&p    = %p\n", (void *) &p));
	//printf("idx: %i\n\n", ft_printf("&p    = %p\n", (void *) &p));
	//printf("idx: %i\n\n", printf("p    = %p\n", (void *) p));
	//printf("idx: %i\n\n", ft_printf("p    = %p\n", (void *) p));

}/*/
