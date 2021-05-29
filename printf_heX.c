#include "ft_printf.h"

void	align_heX(t_flags *flag, int len, int hex)
{
	if (flag->width > flag->precision && flag->left_align == 0)
	{
		if (flag->precision > len)
			align(flag->width - flag->precision);
		else if (flag->precision >= 0)
			align (flag->width - len);
		else if (flag->zero == 1)
			align_integer(flag->width - len);
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

int	zero_arg_heX(int arg, t_flags *flag, int len, int hex)
{
	if (flag->precision == -1)
	{
		if (flag->left_align == 0 && flag->width > 0 && flag->precision == -1)
		{
			if (flag->zero == 0 && flag->precision == -1)
				align(flag->width - len);
			else if (flag->zero == 1)
				align_integer(flag->width - len);
			ft_putheX(hex);
			return (flag->width);
		}
	}
	else if (flag->precision > -1 && flag->width >= flag->precision && arg == 0)
	{
		if (flag->left_align == 0)
			align(flag->width - flag->precision);
		if (flag->precision != 0)
			align_integer(flag->precision);
		if (flag->left_align == 1)
			align(flag->width - flag->precision);
		return (flag->width);
	}
	return (-1);
}

int	parse_precision_heX(int arg, t_flags *flag, int len, int hex)
{
	int	idx;

	if (flag->precision == 0 && flag->width == 0)
	{
		if (arg == 0)
			return (0);
	}
	else if (flag->width >= flag->precision && arg == 0)
	{
		idx = zero_arg_heX(arg, flag, len, hex);
		if (idx >= 0)
			return (idx);
	}
	else if (flag->width <= flag->precision)
	{
		align_integer(flag->precision - len);
		ft_putheX(hex);
		return (flag->precision);
	}
	align_heX(flag, len, hex);
	return (-1);
}
