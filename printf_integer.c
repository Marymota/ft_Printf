#include "ft_printf.h"

int	no_precision_integer(int arg, t_flags *flag)
{
	if (flag->precision <= 0 && arg == 0)
	{
		if (flag->precision == 0)
			align(flag->width);
		if (flag->precision == 0 || (flag->left_align == 1 && flag->width == 0))
			return (1);
	}
	return (0);
}

void	parse_width_integer(int arg, t_flags *flag, int minus, int len)
{
	if ((flag->width > len + minus && flag->width > flag->precision))
	{
		if (arg != 0 && flag->precision == 0)
			align (flag->width - len - minus);
		else if (flag->precision >= len + minus)
			align (flag->width - flag->precision - minus);
		else if (flag->width >= len && flag->precision > 0)
			if (flag->zero == 1 || (flag->precision < len + minus && arg != 0))
				align (flag->width - len - minus);
	}
	if (flag->precision == flag->width)
	{
		if (minus == 1)
			ft_putchar_fd('-', 1);
		align_integer(flag->width - len);
		ft_putnbr_fd(arg, 1);
	}
}

void	printf_precision_integer(int arg, t_flags *flag, int minus, int len)
{
	if (flag->zero == 0 && flag->precision <= 0)
	{
		if (flag->width > (len + minus) && flag->precision < 0)
			if (!flag->left_align)
				align(flag->width - (len + minus));
		if (flag->precision <= 0)
			if (minus == 1)
				ft_putchar_fd('-', 1);
	}
	else if (flag->precision > 0 || flag->zero == 1)
	{
		if (minus == 1)
			ft_putchar_fd('-', 1);
		if (flag->left_align == 0 && flag->width >= flag->precision)
		{
			if (flag->width > (len + minus) && flag->precision < 0)
				align_integer(flag->width - (len + minus));
			else if (flag->precision != -1)
				align_integer(flag->precision - len);
		}
		else if (flag->left_align == 1 || flag->width < flag->precision)
			align_integer(flag->precision - len);
	}
	print_left_align_int(arg, flag, len, minus);
}

void	print_left_align_int(int arg, t_flags *flag, int len, int minus)
{
	int	size;

	if (arg == -2147483648)
	{
		ft_putnbr_fd(214748364, 1);
		ft_putnbr_fd(8, 1);
	}
	else
		ft_putnbr_fd(arg, 1);
	if (flag->precision > len)
		size = flag->width - flag->precision - minus;
	else
		size = flag->width - (len + minus);
	if (flag->left_align == 1 && size > 0)
		align(size);
}

int	return_integer(t_flags *flag, int idx, int len, int minus)
{
	idx = len + minus;
	if (flag->width < flag->precision)
	{
		if (flag->precision >= len)
			idx = flag->precision + minus;
		else if (flag->precision < len && flag->left_align == 1)
			idx = len + minus;
		else if (flag->width == 0 && flag->precision < (len + minus))
			idx = flag->width + len + minus;
	}
	else if (flag->width > 0 && flag->width > flag->precision)
	{
		if (flag->width > len)
			idx = flag->width;
		else if (flag->precision > len)
			idx = flag->precision + minus;
		else if (flag->precision < len)
			idx = len + minus;
		else if (flag->width != 0)
			idx = flag->width;
	}
	return (idx);
}
