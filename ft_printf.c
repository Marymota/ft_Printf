#include "ft_printf.h"

int	return_char(t_flags *flag, int idx)
{
	if (flag->width)
		idx = flag->width;
	else
		idx = 1;
	return (idx);
}

int	return_string(t_flags *flag, int idx, int len)
{
	idx = len;
	if (flag->width <= flag->precision)
	{
		if (flag->precision >= 0 && flag->precision < len)
			idx = flag->precision;
	}
	else if (flag->width == 0)
	{
		if (flag->precision == -1)
		{
			if (len == -1)
				idx = 0;
		}
	}
	else if (flag->width >= 0)
	{
		if (flag->precision >= 0 || flag->width >= len)
			idx = flag->width;
	}
	return (idx);
}

int	return_integer(t_flags *flag, int idx, int len, int minus)
{
	idx = len;
	if (flag->width < flag->precision)
	{
		if (flag->precision > len)
			idx = flag->precision + minus;
		else if (flag->precision < len)
			idx = flag->width + len + minus;
	}
	else if (flag->width > 0 && flag->width > flag->precision)
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
	return (idx);
}

int	return_unsigned(ssize_t arg, t_flags *flag, int len)
{
	int	size;

	size = 0;
	if (flag->precision > len)
		size = flag->width - flag->precision;
	else if (flag->width > len)
		size = flag->width - len;
	if (flag->precision > len || flag->width > len)
		printf_precision_unsigned(flag, size, len);
	ft_putunbr(arg);
	if (flag->left_align == 1)
		if (size > 0)
			align(size);
	if (flag->width >= flag->precision && flag->width > len)
		if (flag->width > len)
			return (flag->width);
	if (flag->width < flag->precision)
	{
		if (flag->precision > len)
			return (flag->precision);
		else if (flag->precision < len)
			return (flag->width + len);
	}
	return (len);
}

void	align(int len)
{
	while (len--)
		ft_putchar_fd(' ', 1);
}

void	align_integer(int size)
{
	if (size > 0)
		while (size--)
			ft_putchar_fd('0', 1);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s++)
		++i;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n * -1, fd);
	}
	else if (n / 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

void	ft_putunbr(ssize_t n)
{	
	if (n < 0)
		n = 4294967296 + n;
	if (n / 10)
	{
		ft_putnbr_fd(n / 10, 1);
		ft_putchar_fd(n % 10 + '0', 1);
	}
	else
		ft_putchar_fd(n + '0', 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s || fd < 0)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

void	ft_putaddr(unsigned long n)
{
	if (n > 15)
	{
		ft_putaddr(n / 16);
		ft_putaddr(n % 16);
	}
	else if (n < 10)
	{
		ft_putchar_fd(n + '0', 1);
	}
	else
	{
		if (n == 10)
			ft_putchar_fd('a', 1);
		else if (n == 11)
			ft_putchar_fd('b', 1);
		else if (n == 12)
			ft_putchar_fd('c', 1);
		else if (n == 13)
			ft_putchar_fd('d', 1);
		else if (n == 14)
			ft_putchar_fd('e', 1);
		else if (n == 15)
			ft_putchar_fd('f', 1);
	}
}

void	ft_puthex(unsigned int n)
{
	if (n > 15)
	{
		ft_puthex((n / 16));
		ft_puthex((n % 16));
	}
	else if (n < 10)
	{
		ft_putchar_fd(n + '0', 1);
	}
	else
	{
		if (n == 10)
			ft_putchar_fd('a', 1);
		else if (n == 11)
			ft_putchar_fd('b', 1);
		else if (n == 12)
			ft_putchar_fd('c', 1);
		else if (n == 13)
			ft_putchar_fd('d', 1);
		else if (n == 14)
			ft_putchar_fd('e', 1);
		else if (n == 15)
			ft_putchar_fd('f', 1);
	}
}

void	ft_putheX(unsigned int n)
{
	count_hex(n);
	if (n > 15)
	{
		ft_putheX((n / 16));
		ft_putheX((n % 16));
	}
	else if (n < 10)
	{
		ft_putchar_fd(n + '0', 1);
	}
	else
	{
		if (n == 10)
			ft_putchar_fd('A', 1);
		else if (n == 11)
			ft_putchar_fd('B', 1);
		else if (n == 12)
			ft_putchar_fd('C', 1);
		else if (n == 13)
			ft_putchar_fd('D', 1);
		else if (n == 14)
			ft_putchar_fd('E', 1);
		else if (n == 15)
			ft_putchar_fd('F', 1);
	}
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	print_left_align_int(int arg, t_flags *flag, int len, int minus)
{
	int	size;

	if (flag->precision > 0 || flag->precision == -1 || flag->width > 0)
	{
		if (flag->width > len && flag->precision < 0 && flag->zero == 0)
			align(flag->width - len);
		if (arg == -2147483648)
		{
			ft_putnbr_fd(214748364, 1);
			ft_putnbr_fd(8, 1);
		}
		else
			ft_putnbr_fd(arg, 1);
	}
	if (flag->precision > len)
		size = flag->width - flag->precision - minus;
	else
		size = flag->width - len - minus;
	if (flag->left_align == 1 && size > 0)
		align(size);
}

int	min(int arg)
{
	int	minus;

	minus = 0;
	if (arg < 0)
		minus = 1;
	return (minus);
}

int	int_size(int i)
{
	int	idx;

	idx = 0;
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

int	uint_size(unsigned int i)
{
	int	idx;

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

int	count_addr(unsigned long n)
{
	int	idx;

	idx = 0;
	while (n > 0)
	{
		n = n / 16;
		++idx;
	}	
	return (idx);
}

int	count_hex(unsigned int n)
{
	int	idx;

	idx = 0;
	while (n > 0)
	{
		n = n / 16;
		++idx;
	}
	return (idx);
}

int	count_width(const char *format, va_list args, t_flags *flag)
{
	int	width;

	width = 0;
	if (flag->asterisk == 1)
	{
		flag->asterisk = va_arg(args, int);
		return (flag->asterisk);
	}
	if (ft_isdigit(*format))
	{
		while (ft_isdigit(*format))
		{
			width = width * 10 + (*format - '0');
			++format;
		}
	}
	return (width);
}

int	count_digits(const char *format, va_list args, t_flags *flag)
{
	int	idx;

	idx = 0;
	if (flag->precision >= 0)
	{
		flag->precision = count_width(format, args, flag);
		idx = int_size(flag->precision);
	}
	else
	{
		flag->width = count_width(format, args, flag);
		idx = int_size(flag->width);
	}
	return (idx);
}

int	printf_truncate(char *arg, t_flags *flag)
{
	int	idx;
	int	count_precision;

	idx = 0;
	count_precision = flag->precision;
	if (flag->left_align == 0)
	{
		if (flag->width - flag->precision > 0)
			align(flag->width - flag->precision);
	}
	while (count_precision--)
	{
		ft_putchar_fd(*arg++, 1);
		++idx;
	}
	if (flag->left_align == 1)
	{
		if (flag->width - flag->precision > 0)
			align(flag->width - flag->precision);
	}
	return (idx);
}

void	printf_precision(char *arg, t_flags *flag, int size)
{
	if (flag->width == 0)
		ft_putstr_fd(arg, 1);
	else if (flag->left_align == 0)
	{
		if (size > 0)
			align(size);
		ft_putstr_fd(arg, 1);
	}
	else if (flag->left_align == 1)
	{
		ft_putstr_fd(arg, 1);
		if (size > 0)
			align(size);
	}
}

void	printf_precision_integer(int arg, t_flags *flag, int minus, int len)
{
	if (flag->precision >= 0 || flag->zero == 1)
	{
		if (flag->left_align == 0 && flag->width > flag->precision)
		{
			if (flag->precision == 0 && flag->width > flag->precision)
				align(flag->width - flag->precision - len - minus);
			else if (flag->precision != -1)
				align(flag->width - flag->precision - minus);
			if (minus == 1)
				ft_putchar_fd('-', 1);
			if (flag->precision != -1)
				align_integer(flag->precision - len);
			else
				align_integer(flag->width - minus - len);
		}
		if (flag->left_align == 1 || flag->width < flag->precision)
		{
			if (minus == 1)
				ft_putchar_fd('-', 1);
			align_integer(flag->precision - len);
		}
	}
	print_left_align_int(arg, flag, len, minus);
}

void	printf_precision_unsigned(t_flags *flag, int size, int len)
{
	if (flag->left_align == 0)
	{
		if (flag->width > flag->precision)
		{
			if (flag->precision == 0 && flag->width > flag->precision)
				align(flag->width - flag->precision - len);
			else if (flag->precision != -1)
				align(size);
			if (flag->width > flag->precision && flag->precision != -1)
				align_integer(flag->precision - len);
			else if (flag->precision != -1 || flag->left_align)
				align_integer(flag->width - flag->precision - len);
			else
				align_integer(flag->width - len);
		}
		if (flag->width < flag->precision)
			align_integer(flag->precision - len);
	}
	if (flag->left_align == 1)
	{
		if (flag->precision > len)
			align_integer(flag->precision - len);
	}
}

void	parse_width_integer(int arg, t_flags *flag, int minus, int len)
{
	if (flag->precision <= 0)
	{
		if (arg == 0 && flag->precision == 0)
			align(flag->width);
		else if (flag->left_align == 1)
		{
			if (minus == 1)
				ft_putchar_fd('-', 1);
			ft_putnbr_fd(arg, 1);
			align(flag->width - len - minus);
		}
	}
	if (flag->precision == flag->width)
	{
		if (minus == 1)
			ft_putchar_fd('-', 1);
		align_integer(flag->width - len);
		ft_putnbr_fd(arg, 1);
	}
}

int	no_precision_integer(int arg, t_flags *flag, int minus, int len)
{
	if (flag->precision <= 0)
	{
		if (arg == 0 && flag->precision == 0)
			align(flag->width);
		else if (flag->left_align == 1)
			parse_width_integer(arg, flag, minus, len);
		if ((!arg && flag->precision == 0) || flag->left_align == 1)
			return (1);
	}
	return (0);
}

int	no_precision_unsigned(int arg, t_flags *flag, int len)
{
	if (flag->precision < 0)
	{
		if (flag->left_align == 1)
		{
			ft_putunbr(arg);
			align(flag->width - len);
			return (flag->width);
		}
		if (flag->width == 0 && flag->zero == 0)
		{
			ft_putunbr(arg);
			return (1);
		}
		else if (flag->zero == 0)
		{
			align(flag->width - len);
			ft_putunbr(arg);
			return (flag->width);
		}
	}
	return (-1);
}

int	max_int_unsigned(int arg, t_flags *flag, int len)
{
	if (arg > 2147483647)
	{
		if (flag->width > len && flag->precision == 0)
		{
			if (flag->zero == 1 && flag->left_align == 0)
			{
				align(flag->width - len);
				ft_putunbr(arg);
				return (flag->width);
			}
		}
		else if (flag->width < len && flag->precision == 0)
		{
			if (flag->zero == 0 || flag->left_align == 0)
			{
				ft_putunbr(arg);
				return (len);
			}
		}
	}
	return (-1);
}

int	parse_unsigned(int arg, t_flags *flag, int len, int idx)
{
	idx = max_int_unsigned(arg, flag, len);
	if (flag->width < len && flag->precision == -1)
	{
		ft_putunbr(arg);
		return (len);
	}
	else if (flag->precision <= 0)
	{
		idx = no_precision_unsigned(arg, flag, len);
		if (flag->precision == 0 && arg == 0)
		{
			align(flag->width);
			return (flag->width);
		}
	}
	else if (flag->precision == flag->width)
	{
		align_integer(flag->width - len);
		ft_putunbr(arg);
		return (flag->width);
	}
	return (idx);
}

int	parse_width_string (char *arg, t_flags *flag)
{
	int	idx;
	int	len;
	int	size;

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

int	parse_precision_string (char *arg, t_flags *flag)
{
	int	idx;
	int	len;
	int	size;

	idx = 0;
	len = ft_strlen(arg);
	size = 0;
	if (flag->precision < len)
		idx = printf_truncate(arg, flag);
	else if (flag->precision >= len)
	{
		if (flag->precision < flag->width)
			size = flag->width - len;
		else if (flag->precision >= flag->width)
			size = flag->precision - len;
		else if (flag->precision == 0)
			align(flag->width);
		printf_precision(arg, flag, size);
	}
	return (idx);
}

int	parse_hexadecimal(ssize_t address, t_flags *flag)
{
	int	idx;
	int	len;

	idx = 0;
	len = count_addr(address);
	flag->width = flag->width - len - 2;
	if (flag->width > 0)
	{
		idx = flag->width;
		align(flag->width);
	}
	return (idx);
}

int	printf_c (va_list args, t_flags *flag, int idx)
{
	int	arg;

	arg = va_arg(args, int);
	if (flag->width > 1 && flag->left_align == 0)
	{
		align(flag->width - 1);
	}
	ft_putchar_fd(arg, 1);
	if (flag->width > 1 && flag->left_align == 1)
	{
		align(flag->width - 1);
	}
	idx = return_char(flag, idx);
	return (idx);
}

int	printf_s (va_list args, t_flags *flag, int idx)
{
	char	*arg;
	int		len;

	arg = va_arg(args, char *);
	if (arg == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	len = ft_strlen(arg);
	if (flag->precision >= 0)
		parse_precision_string(arg, flag);
	else
	{
		if (flag->width > 0 && flag->left_align == 0)
			parse_width_string(arg, flag);
		ft_putstr_fd(arg, 1);
		if (flag->width > 0 && flag->left_align == 1)
			parse_width_string(arg, flag);
	}
	idx = return_string(flag, idx, len);
	return (idx);
}

int	printf_p (va_list args, t_flags *flag, int idx)
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
		ft_putaddr(address);
		idx += count_addr(address);
	}
	else
	{
		flag->width -= 3;
		if (flag->width > 0 && flag->left_align == 0)
			idx += parse_hexadecimal(address, flag) + 6;
		write (1, "(nil)", 5);
		if (flag->precision <= 3 && flag->width <= 3)
			idx += 3;
	}
	if (flag->width > 0 && flag->left_align == 1)
		idx += parse_hexadecimal(address, flag);
	return (idx + 2);
}

int	printf_d (va_list args, t_flags *flag, int idx)
{
	int	arg;
	int	len;
	int	minus;

	arg = va_arg(args, int);
	minus = min(arg);
	if (minus)
		arg = -arg;
	len = int_size(arg);
	if (no_precision_integer(arg, flag, minus, len))
		return (flag->width);
	if (flag->precision == flag->width)
		parse_width_integer(arg, flag, minus, len);
	if (flag->width && flag->precision == flag->width)
		return (flag->width + minus);
	else if (flag->precision == flag->width)
		return (len);
	printf_precision_integer(arg, flag, minus, len);
	return (return_integer(flag, idx, len, minus));
}

int	printf_u (va_list args, t_flags *flag, int idx)
{
	size_t	arg;
	int		len;

	arg = va_arg(args, int);
	len = uint_size(arg);
	idx = parse_unsigned(arg, flag, len, idx);
	if (idx >= 0)
		return (idx);
	return (return_unsigned(arg, flag, len));
}

int	printf_x (va_list args, t_flags *flag, int idx)
{
	int		arg;
	size_t	hex;
	int		len;

	idx = 0;
	arg = va_arg(args, int);
	hex = (size_t)arg;
	len = count_hex(hex);
	if (hex == 0)
	{
		len = 1;
		++idx;
	}
	if (flag->left_align == 1)
	{
		if (flag->zero == 1 && flag->precision == -1 && arg != 0)
		{	
			ft_puthex(hex);
			if (flag->width > len)
			{
				align(flag->width - len);
				return (flag->width);
			}
			return (len);
		}
	}
	if (flag->precision == 0 && flag->width == 0)
	{
		if (arg == 0)
			return (0);
	}
	else if (flag->width >= flag->precision && arg == 0)
	{
		if (flag->precision == -1)
		{
			if (flag->left_align == 0)
			{
				if (flag->width > 0)
				{
					if (flag->zero == 0)
					{
						align(flag->width - len);
						ft_puthex(hex);
						return (flag->width);
					}
					else if (flag->zero == 1)
					{	
						align_integer(flag->width - len);
						ft_puthex(hex);
						return (flag->width);
					}
				}
			}
		}
		else if (flag->precision > -1)
		{
			if (flag->left_align == 0)
			{
				align(flag->width - flag->precision);
			}
			if (flag->precision != 0)
				align_integer(flag->precision);
			if (flag->left_align == 1)
			{
				align(flag->width - flag->precision);
			}
			return (flag->width);
		}
		else if (flag->width > len)
		{
			align(flag->width - len);
			ft_puthex(hex);
		}
	}
	else if (flag->width <= flag->precision)
	{
		align_integer(flag->precision - len);
		ft_puthex(hex);
		return (flag->precision);
	}
	if (flag->width != 0)
	{
		if (flag->width > flag->precision)
		{
			if (flag->left_align == 0)
			{
				if (flag->precision > len)
					align(flag->width - flag->precision);
				else if (flag->precision >= 0)
					align (flag->width - len);
				else if (flag->zero == 1)
				{
					if (flag->precision == -1)
						align_integer(flag->width - len);
				}
			}
		}
	}
	if (flag->precision > len)
		align_integer(flag->precision - len);
	ft_puthex(hex);
	if (flag->left_align == 1)
	{
		if (flag->precision >= len)
			align(flag->width - flag->precision);
		else if (flag->precision < len)
			align (flag->width - len);
	}
	if (flag->width == 0 && flag->precision == -1)
		idx = len;
	else if (flag->width > flag->precision)
	{
		if (flag->width > len)
			idx = flag->width;
	}
	else if (flag->precision > flag->width)
	{
		if (flag->precision > len)
			idx = flag->precision;
	}
	else
		idx = len;
	return (idx);
}

int	printf_X (va_list args, t_flags *flag, int idx)
{
	int		arg;
	size_t	hex;
	int		len;

	idx = 0;
	arg = va_arg(args, int);
	hex = (size_t)arg;
	len = count_hex(hex);
	if (hex == 0)
	{
		len = 1;
		++idx;
	}
	if (flag->left_align == 1)
	{
		if (flag->zero == 1 && flag->precision == -1 && arg != 0)
		{	
			ft_putheX(hex);
			if (flag->width > len)
			{
				align(flag->width - len);
				return (flag->width);
			}
			return (len);
		}
	}
	if (flag->precision == 0 && flag->width == 0)
	{
		if (arg == 0)
			return (0);
	}
	else if (flag->width >= flag->precision && arg == 0)
	{
		if (flag->precision == -1)
		{
			if (flag->left_align == 0)
			{
				if (flag->width > 0)
				{
					if (flag->zero == 0)
					{
						align(flag->width - len);
						ft_putheX(hex);
						return (flag->width);
					}
					else if (flag->zero == 1)
					{	
						align_integer(flag->width - len);
						ft_putheX(hex);
						return (flag->width);
					}
				}
			}
		}
		else if (flag->precision > -1)
		{
			if (flag->left_align == 0)
			{
				align(flag->width - flag->precision);
			}
			if (flag->precision != 0)
				align_integer(flag->precision);
			if (flag->left_align == 1)
			{
				align(flag->width - flag->precision);
			}
			return (flag->width);
		}
		else if (flag->width > len)
		{
			align(flag->width - len);
			ft_putheX(hex);
		}
	}
	else if (flag->width <= flag->precision)
	{
		align_integer(flag->precision - len);
		ft_putheX(hex);
		return (flag->precision);
	}
	if (flag->width != 0)
	{
		if (flag->width > flag->precision)
		{
			if (flag->left_align == 0)
			{
				if (flag->precision > len)
					align(flag->width - flag->precision);
				else if (flag->precision >= 0)
					align (flag->width - len);
				else if (flag->zero == 1)
				{
					if (flag->precision == -1)
						align_integer(flag->width - len);
				}
			}
		}
	}
	if (flag->precision > len)
		align_integer(flag->precision - len);
	ft_putheX(hex);
	if (flag->left_align == 1)
	{
		if (flag->precision >= len)
			align(flag->width - flag->precision);
		else if (flag->precision < len)
			align (flag->width - len);
	}
	if (flag->width == 0 && flag->precision == -1)
		idx = len;
	if (flag->width > flag->precision)
	{
		if (flag->width > len)
			idx = flag->width;
	}
	else if (flag->precision > flag->width)
	{
		if (flag->precision > len)
			idx = flag->precision;
	}
	else
		idx = len;
	return (idx);
}

int	get_specifier(const char *format, va_list args, t_flags *flag)
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
	else if (*format == 'X')
		idx = printf_X(args, flag, idx);
	else if (*format == '%')
	{
		ft_putchar_fd('%', 1);
		++idx;
	}
	return (idx);
}

void	parse_asterisk(const char *format, va_list args, t_flags *flag)
{
	if (flag->precision >= 0)
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

int	get_flags(const char *format, va_list args, t_flags *flag)
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
	else if (*format == '0' && flag->precision == -1)
		flag->zero = 1;
	else
		return (0);
	return (1);
}

void	init(t_flags *flag)
{
	flag->width = 0;
	flag->left_align = 0;
	flag->asterisk = 0;
	flag->precision = -1;
	flag->zero = 0;
}

int	parse_format(const char *fmt, va_list args, t_flags *flag, int idx)
{
	init(flag);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			++fmt;
			while (*fmt == '-' || *fmt == '*' || *fmt == '.' || ft_isdigit(*fmt))
			{
				if (get_flags(fmt, args, flag))
					++fmt;
				else if (ft_isdigit(*fmt))
					fmt += count_digits(fmt, args, flag);
			}
			idx += get_specifier(fmt, args, flag);
			init(flag);
		}
		else
		{
			ft_putchar_fd(*fmt, 1);
			++idx;
		}
		++fmt;
	}
	return (idx);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flag;
	int		done;
	int		idx;

	idx = 0;
	va_start(args, format);
	done = parse_format(format, args, &flag, idx);
	va_end (args);
	return (done);
}
