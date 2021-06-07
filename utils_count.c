#include "ft_printf.h"

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
	if (n == 0)
		return (1);
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
