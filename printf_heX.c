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

void	parse_precision_heX(int arg, t_flags *flag, int len)
{
	if (flag->left_align == 1)
	{
		if (flag->precision >= len)
			align_integer(flag->precision - len);
		ft_putheX(arg);
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
		ft_putheX(arg);
}
