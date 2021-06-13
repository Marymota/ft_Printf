#include "ft_printf.h"

int	printf_p (va_list args, t_flags *flag, int idx)
{
	void	*arg;
	ssize_t	address;

	arg = va_arg(args, void *);
	address = (ssize_t)(arg);
	if (address != 0)
	{
		if (flag->width == 0 && flag->precision == -1)
			idx = parse_hexadecimal(address, flag);
		else if (flag->width > 0 && flag->left_align == 0)
			idx = parse_hexadecimal(address, flag);
		write (1, "0x", 2);
		ft_putaddr(address);
	}
	else if (address == 0)
	{
		if (flag->left_align == 0)
			idx = parse_hexadecimal(address, flag);
		write (1, "(nil)", 5);
	}
	if (flag->width > 0 && flag->left_align == 1)
		idx = parse_hexadecimal(address, flag);
	if (address == 0 && (flag->width == 0 && flag->precision == -1))
		return (5);
	return (idx);
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
	if (arg == 0 && (flag->precision == 0 && flag->width == 0))
		return (0);
	if (flag->left_align == 0 && flag->width > flag->precision)
		parse_width_integer(arg, flag, minus, len);
	if (no_precision_integer(arg, flag))
		if (flag->width >= len)
			return (flag->width + minus);
	if (flag->precision == flag->width)
		parse_width_integer(arg, flag, minus, len);
	if (len >= flag->width && flag->precision == flag->width)
		return (len + minus);
	else if (len < flag->width && flag->precision == flag->width)
		return (flag->width + minus);
	printf_precision_integer(arg, flag, minus, len);
	return (return_integer(flag, idx, len, minus));
}

int	printf_u (va_list args, t_flags *flag, int idx)
{
	size_t	arg;
	int		len;

	arg = va_arg(args, int);
	len = uint_size(arg);
	if (arg == 0 && flag->precision == 0)
	{
		if (flag->width > 0)
		{
			align (flag->width);
			return (flag->width);
		}
		if (len == 1)
			return (flag->width);
		else
			return (flag->width);
	}
	if (idx > 50)
		return (idx);
	return (return_unsigned(arg, flag, len));
}

int	printf_x (va_list args, t_flags *flag, int idx)
{
	int		arg;
	size_t	hex;
	int		tmp;

	tmp = -1;
	arg = va_arg(args, int);
	hex = (size_t)arg;
	idx = count_hex(hex);
	if (hex == 0 && flag->precision == 0)
	{
		if (flag->width)
			align (flag->width);
		return (flag->width);
	}
	if (flag->precision == -1)
	{
		tmp = no_precision_x(hex, flag, idx);
		if (tmp > -1)
			return (tmp);
	}
	parse_precision_hex(arg, flag, idx);
	return (return_x(flag, idx));
}

int	printf_X (va_list args, t_flags *flag, int idx)
{
	int		arg;
	size_t	hex;
	int		tmp;

	tmp = -1;
	arg = va_arg(args, int);
	hex = (size_t)arg;
	idx = count_hex(hex);
	if (hex == 0 && flag->precision == 0)
	{
		if (flag->width)
			align (flag->width);
		return (flag->width);
	}
	if (flag->precision == -1)
	{
		tmp = no_precision_X(hex, flag, idx);
		if (tmp > -1)
			return (tmp);
	}
	parse_precision_heX(arg, flag, idx);
	return (return_x(flag, idx));
}
