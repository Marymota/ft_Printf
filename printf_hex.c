#include "ft_printf.h"

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

void	parse_precision_hex(int arg, t_flags *flag, int len)
{
	if (flag->left_align == 1)
	{
		if (flag->precision >= len)
			align_integer(flag->precision - len);
		ft_puthex(arg);
		if (flag->precision > len && flag->width > flag->precision)
			align(flag->width - flag->precision);
		else if (flag->width - len > 0 && flag->width > flag->precision)
			align(flag->width - len);
	}
	else if (flag->width <= flag->precision)
		align_integer(flag->precision - len);
	else
	{
		if (flag->precision > len && flag->width > len)
		{
			align (flag->width - flag->precision);
			align_integer(flag->precision - len);
		}
		else if (flag->width > len)
			align (flag->width - len);
	}
	if (flag->left_align == 0)
		ft_puthex(arg);
}

int	no_precision_x(int hex, t_flags *flag, int idx)
{
	if (flag->left_align == 0)
	{
		if (flag->width > idx)
		{
			if (flag->zero == 1)
				align_integer(flag->width - idx);
			else
				align(flag->width - idx);
			ft_puthex(hex);
			return (flag->width);
		}
		else
			ft_puthex(hex);
	}
	else if (flag->left_align == 1)
	{
		ft_puthex(hex);
		if (flag->width > idx)
		{
			align(flag->width - idx);
			return (flag->width);
		}
	}
	return (idx);
}

int	return_x(t_flags *flag, int len)
{
	int	idx;

	if (flag->width == 0 && flag->precision == -1)
		idx = len;
	else if (flag->width > flag->precision && flag->width > len)
		idx = flag->width;
	else if (flag->precision >= flag->width && flag->precision > len)
		idx = flag->precision;
	else
		idx = len;
	return (idx);
}
