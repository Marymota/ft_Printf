#include "ft_printf.h"

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

int	min(int arg)
{
	int	minus;

	minus = 0;
	if (arg < 0)
		minus = 1;
	return (minus);
}
