#include "ft_printf.h"

/* FROMATTED OUTPUT FUNCTION 

The printf function prints the optional argument 
under the control of the template string 'format' 
to the stream stdout.
It returns the number of characters printed, or a 
negative value if there was an outpur error

printf() is called with a "format string" that specifies how to format the values of the remaining arguments. 

*/
// *** RETURNS ***
/*	Calculate return value of characters	*/
int return_char(t_flags *flag, int idx)
{
	if (flag->width)
		idx = flag->width;
	else 
		idx = 1;
	return (idx);
}
/*	Calculate return value of strings	*/
int return_string(t_flags *flag, int idx, int len)
{
	idx = len;
	if (flag->width == 0)
	{
		if (flag->precision == -1)
		{
			if (len == -1)
				idx = 0;
			else if (len > 0)
				idx = len;
		}
		else if (flag->precision < len)
			idx = flag->precision;

	}
	else if (flag->width > 0)
	{
		if (flag->precision >= 0)
		{
			if (flag->precision < flag->width)
				idx = flag->width;
			else if (flag->precision < len)
				idx = flag->precision;

		}
		else if (flag->width >= len)
			idx = flag->width;
		else if (flag->width < len)
			idx = len;
	}
	return (idx);
}
/*	Calculate return value of integers	*/
int return_integer(t_flags *flag, int idx, int len, int minus)
{

	if (flag->width < flag->precision)
	{
		if (flag->precision > len)
			idx = flag->precision + minus;
		else if (flag->precision < len)
			idx = flag->width + len + minus;
	}
	else if (flag->width > flag->precision)
	{
		if (flag->width > len)
			idx = flag->width;
		else if (flag->precision > len)
			idx = flag->precision + minus;
		else if (flag->precision < len)
			idx = flag->width + minus;
		else if (flag->width != 0)
			idx = flag->width;
	}
	if (flag->width >= flag->precision && flag->width != 0)
	{
		idx = flag->width;
	}
	else if (flag->precision == -1)
		idx = len;
	return (idx);
}

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
/*	Prints a unsigned number	*/
void	ft_putunbr(ssize_t n)
{	
	
	if (n < 0)
	{
		n = 4294967296 + n;
		//printf("\ntest: %li\n", n);
	}
	
	if (n / 10)
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
/*	Prints spaces to align content based on width, precision & alignement	*/
void	align_integer(int size)
{
		//printf("\ntest: %i %i\n", flag->width, len);

	if (size > 0)
		while (size--)
			ft_putchr('0');
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
	
	//printf("arg = %i\n", i);

	if (i == -2147483648)
		return (10);

	if (i < 10)
		return (1);
	while (i > 9)
	{
		i /= 10;
		++idx;
	}
	if (i >= 0)
		++idx;
	
	return (idx);
}
/*	Counts digits of unsigned numeric values*/
int uint_size(unsigned int i)
{
	int idx;
	idx = 0;
	
	if (i < 10)
		return (1);
	while (i > 9)
	{
		i /= 10;
		++idx;
	}
	if (i)
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
	//printf("\nret= %i\n", ret);

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
		//printf("\nfmt= %i\n", fmt);

	}
	else 
	{
		flag->width = count_width(format, args, flag);
		fmt = int_size(flag->width);
	}
	//printf("\nflag->precision= %i\n", flag->precision);
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
/*	If precision is less than the length of the string, the string will be truncate */
int printf_truncate_integer(int arg, t_flags *flag)
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
			align_integer(width - precision);
		while (count_precision--)
		{
			ft_putnbr(arg);
			++idx;	
		}
	}
	else if (flag->left_align == 1)
	{
		while (count_precision--)
		{
			ft_putnbr(arg);
			++idx;	
		}
		if (width - precision > 0)
			align_integer(width - precision);
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
int printf_precision_integer(int arg, t_flags *flag, int size, int minus)
{
	int	idx;
	int len;


	len = int_size(arg);

	idx = 0;

	if (flag->precision >= len)
	{
		if (flag->precision < flag->width)
		{
			size = flag->width - flag->precision;
		}	
		else if (flag->precision >= flag->width )
			size = flag->precision - len;
	}

	if (flag->left_align == 0)
	{
		if (flag->width > flag->precision)
		{
			size = flag->width - flag->precision;
			if (minus)
				--size;
			if (flag->precision == 0 && flag->width > flag->precision)
			{
				if (arg != 0)
					align(size - len);
			}
			else if (flag->precision != -1)
				align(size);
			if (minus == 1)
			{
				idx += ft_putchr('-');
			}
				
			if (flag->width > flag->precision && flag->precision != -1)
				align_integer(flag->precision - len);
			else if (flag->precision != -1)
				align_integer(size - len);
			else if (flag->left_align)
				align_integer(size - len);
			else 
				align_integer(flag->width - minus - len);
		}
		if (flag->width < flag->precision)
		{
			if (minus == 1)
			{
				idx += ft_putchr('-');
			}
			align_integer(size);
		}
	}

	if (flag->left_align == 1)
	{
		if (minus == 1)
		{
			idx += ft_putchr('-');
		}
		if (flag->precision > len)
		{
			size = flag->precision - len;
			align_integer(size);
		}
	}
	if (flag->precision > flag->width)
		idx += flag->precision;
	else
		idx += flag->width;
	return (idx);
}
/*	Prints the extra width after subtracting the content length */
int printf_precision_unsigned(unsigned int num, t_flags *flag, int size, int minus)
{
	int	idx;
	int len;

	len = int_size(num);
	idx = 0;

	if (flag->precision >= len)
	{
		if (flag->precision < flag->width)
		{
			size = flag->width - flag->precision;
		}	
		else if (flag->precision >= flag->width )
			size = flag->precision - len;
	}

	if (flag->left_align == 0)
	{
		if (flag->width > flag->precision)
		{
			size = flag->width - flag->precision;
			if (minus)
				--size;
			if (flag->precision == 0 && flag->width > flag->precision)
			{
				if (num != 0)
					align(size - len);
			}
			else if (flag->precision != -1)
				align(size);

			if (flag->width > flag->precision && flag->precision != -1)
				align_integer(flag->precision - len);
			else if (flag->precision != -1)
				align_integer(size - len);
			else if (flag->left_align)
				align_integer(size - len);
			else 
				align_integer(flag->width - minus - len);
		}
		if (flag->width < flag->precision)
		{
			align_integer(size);
		}
	}

	if (flag->left_align == 1)
	{

		if (flag->precision > len)
		{
			size = flag->precision - len;
			align_integer(size);
		}
	}
	if (flag->precision > flag->width)
		idx += flag->precision;
	else
		idx += flag->width;
	return (idx);
}
/*	Prints the extra width after subtracting the content length */
int parse_width_string (char *arg, t_flags *flag)
{
	int	idx;
	int	len;
	int size;

	idx = 0;
	len = ft_strlen(arg);
	size = flag->width - len;
	if (size > 0)
	{
		idx = size;
		align(size);
	}
	return (idx);
}
/*	Prints the extra width after subtracting the content length */
int parse_width_integer (int arg, t_flags *flag, int size)
{
	int	idx;
	int	len;

	idx = 0;
	len = int_size(arg);

	if (flag->zero == 0)
	{
		idx = flag->precision;
		align_integer(flag->precision);
	}
	else if (size > flag->precision)
	{
		if (flag->precision > 0)
			idx = flag->precision - len;
		else 
			idx = size;
		align_integer(idx);
	}

	else
	{
		idx = flag->precision;
		align_integer(flag->precision - len);
	}
	return (idx);
}
/*	Returns the necessary extra width space when precision is used*/
int parse_precision_string (char *arg, t_flags *flag)
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

//	PRINT_INTS ***
/*	Prints max ints	*/
void print_max_int(int arg, t_flags *flag, int len)
{
	if (flag->precision > 0 || flag->precision == -1 || flag->width > 0)
	{
		if (flag->width > len && flag->precision < 0 && flag->zero == 0)
			align(flag->width - len);
		if (arg == -2147483648)
		{
			ft_putnbr(214748364);
			ft_putnbr(8);
		}
		else
			ft_putnbr(arg);
	}
}

//	PRINT_SPECIFIERS ***
/*	Prints and aligns one character	*/
int printf_c (va_list args, t_flags *flag, int idx)
{
	int	arg;

	arg = va_arg(args, int);
	if (flag->width > 1 && flag->left_align == 0)
	{
		align(flag->width - 1);
	}
	ft_putchr(arg);
	if (flag->width > 1 && flag->left_align == 1)
	{
		align(flag->width - 1);
	}
	idx = return_char(flag, idx);
	return (idx);
}
/*	Processes the printing of strings	*/
int printf_s (va_list args, t_flags *flag, int idx)
{
	char	*arg;
	int len;

	arg = va_arg(args, char *);
	len = ft_strlen(arg);
	if (flag->precision >= 0)
		parse_precision_string(arg, flag);
	else 
	{
		if (flag->width > 0 && flag->left_align == 0)
			parse_width_string(arg, flag);
		ft_putstr(arg);
		if (flag->width > 0 && flag->left_align == 1)
			parse_width_string(arg, flag);
	}
	idx = return_string(flag, idx, len);
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
int printf_d (va_list args, t_flags *flag, int idx)
{
	int arg;
	int size;
	int len;
	int minus;

	size = 0;
	arg = va_arg(args, int);
	
	
	idx = 0;
	minus = 0;
	//printf("\n la= %i, w= %i, p= %i, z= %i\n", flag->left_align, flag->width, flag->precision , flag->zero);

		//printf("\nflag->precision= %i\n", flag->precision);

	if (arg < 0)
	{
		minus = 1;
		arg = -arg;	
	}

	len = int_size(arg);
	
	if (flag->precision < 0)
	{
		if (flag->left_align == 1)
		{
			if (minus == 1)
			ft_putchr('-');
			ft_putnbr(arg);
			align(flag->width - len - minus);
			return (flag->width);
		}
	}
	if (arg == 0)
	{
		if (flag->precision == 0)
		{
			align(flag->width);
			return (flag->width);
		}
	}
	if (flag->precision == flag->width)
	{
		if (minus == 1)
		{
			ft_putchr('-');
		}
		align_integer(flag->width - len);
		ft_putnbr(arg);
		if (flag->width > 0)
			return(flag->width + minus);
		else 
			return(len);
	}
	if (flag->precision > len)
		size = flag->width - flag->precision - minus;
	else
		size = flag->width - len - minus;


	if (flag->precision >= 0 || flag->zero == 1)
	{
		idx = printf_precision_integer(arg, flag, size, minus);
	}
	print_max_int(arg, flag, len);

	
	if (flag->left_align == 1)
	{
		if (size > 0)
			align(size);
	}
	idx = return_integer(flag, idx, len, minus);
	return (idx);
}
/*	Processes the printing of digits	*/
int printf_u (va_list args, t_flags *flag, int idx)
{
	size_t arg;
	int len;
	
	int minus;

	arg = va_arg(args, size_t);
	len = uint_size(arg);

	//printf("\ntest: %li\n", arg);

	if (flag->left_align == 1)
	{
		if (arg >= 10)
			len = uint_size((size_t)arg);
		else 
			len = 1;
	}
	else if (flag->left_align == 0)
	{
		if (arg >= 10)
			len = uint_size((size_t)arg);
		else if (arg < 10)
			len = 1;
		else
			uint_size((size_t)arg);
	}

	
		
	idx = 0;
	minus = 0;

	if (flag->precision < 0 && flag->width == 0)
	{
		ft_putunbr(arg);
	}
	else if (flag->precision == 0 && flag->width == 0)
	{
		if (arg == 0)
			return (0);
	}
	else if (flag->precision >= flag->width)
	{
		align_integer(flag->precision - len);
		ft_putunbr(arg);
	}
	else if (flag->width >= flag->precision)
	{
		if (flag->left_align == 1)
		{
			if (flag->precision > len)
				align_integer(flag->precision - len);
			ft_putunbr(arg);
			if (flag->precision >= len)
				align(flag->width - flag->precision);
			else if (flag->precision < len)
				align(flag->width - len);
		}
		else if (flag->left_align == 0)
		{
			if (flag->width > flag->precision)
			{
				if (flag->precision >= len)
					align(flag->width - flag->precision);
				else if (flag->precision < len)
					align_integer(flag->width - len);
			}
			if (flag->precision > len)
				align_integer(flag->precision - len);
			ft_putunbr(arg);
		}
		else	
			return (0);
	}

//	if (arg == 0)
//	{
//		if (flag->precision == 0)
//		{
//			align(flag->width);
//			return (flag->width);
//		}
//	}
//
//	if (flag->precision == flag->width)
//	{
//
//		align_integer(flag->width - len);
//		ft_putunbr(arg);
//		if (flag->width > 0)
//			return(flag->width + minus);
//		else 
//			return(len);
//	}
//
//	if (flag->precision < 0 && flag->width == 0)
//	{
//		if (flag->left_align == 1)
//		{
//			ft_putunbr(arg);
//			return (flag->width);
//		}
//		else 
//		{
//			align(flag->width - len - minus);
//			return (flag->width);
//		}
//	}
//
//	if (flag->precision > len)
//		size = flag->width - flag->precision;
//	else
//		size = flag->width - len;
//
//	if (flag->precision >= 0 || flag->zero == 1)
//	{
//		idx = printf_precision_unsigned(arg, flag, size, minus);
//	}
//	//print_max_int(arg, flag, len);
//
//
//	if (flag->left_align == 1)
//	{
//		if (size > 0)
//			align(size - minus);
//	}
	idx = return_integer(flag, idx, len, minus);
	return (idx);
}
/*	Processes the printing of hexadecimals	*/
int printf_x (va_list args, t_flags *flag, int idx)
{
	int	arg;
	size_t	address;
	int size;
	int len;
		
	idx = 0;
	size = 0;
	len = 0;
	arg = va_arg(args, int);
	address = (size_t)arg;
	len = count_hex(address);

	if (address == 0)
	{
		len = 1;
		++idx;
	}
	//printf("\ntest: %i\n", len);
	if ( flag->precision == 0)
		return (0);

	if (flag->precision > len)
	{
		size = flag->precision - len;
		idx += size;
		align_integer(size);
	}
	if (flag->width > 0 && flag->left_align == 0)
		idx += ft_putaddr(address, idx);
	else 
	{
		idx += ft_putaddr(address, idx);
		if (flag->width > 0 && flag->left_align == 1)
		{
			if (flag->width > flag->precision)
			{
				size = flag->width - flag->precision;
					align(size);
			}
		}
	}
	//idx += parse_hexadecimal(address, flag);
	return (idx);
}

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
	else if (*format == 'd' || *format == 'i')
		idx = printf_d(args, flag, idx);
	else if (*format == 'u')
		idx = printf_u(args, flag, idx);
	else if (*format == 'x')
		idx = printf_x(args, flag, idx);
	//else if (*format == 'X')
	//	idx = printf_X(args, flag, idx);
	else if (*format == '%')
		idx = ft_putchr('%');
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
	else if (*format == '0')
		flag->zero = 1;
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
	flag->zero = 0;
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
			while (*format == '-' || *format == '*' || *format == '.' || *format == '0' || is_digit(format))
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

	//printf("  idx: %i\n\n", printf(" *%-*.*u* *%*.*u* ", 4, 5, 10, 10, 21, -10));
	//printf("  idx: %i\n\n", ft_printf(" *%-*.*u* *%*.*u* ", 4, 5, 10, 10, 21, -10));
//
	//printf("  idx: %i\n\n", printf(" *%-*.*u* *%*.*u* ", 6, 2, 102, 10, 21, -101));
	//printf("  idx: %i\n\n", ft_printf(" *%-*.*u* *%*.*u* ", 6, 2, 102, 10, 21, -101));
//
	//printf("  idx: %i\n\n", printf(" *%*.*u* *%*.*u* ", -6, 2, 102, 10, 21, 101));
	//printf("  idx: %i\n\n", ft_printf(" *%*.*u* *%*.*u* ", -6, 2, 102, 10, 21, 101));

	printf("  idx: %i\n\n", printf(" 0*%0-*.*u*0 0*%0*.*u*0 ", 2, 6, 102, 21, 10, -101));
	printf("  idx: %i\n\n", ft_printf(" 0*%0-*.*u*0 0*%0*.*u*0 ", 2, 6, 102, 21, 10, -101));

	printf("  idx: %i\n\n", printf(" 0*%0-*u*0 0*%0*u*0 ", 21, 1021, 21, -1011));
	printf("  idx: %i\n\n", ft_printf(" 0*%0-*u*0 0*%0*u*0 ", 21, 1021, 21, -1011));
}
/*/
