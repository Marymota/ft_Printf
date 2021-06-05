#include "ft_printf.h"

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

	if ((flag->width > len + minus) && (flag->left_align == 0))
	{
		if ((flag->width > len + minus && flag->width > flag->precision))
		{
			if (arg != 0 && flag->precision == 0)
				align (flag->width - (len + minus));
			else if (flag->precision > len + minus)
				align (flag->width - (flag->precision + minus));
			else if (flag->width >= len && flag->precision > 0)
			{
				if (flag->zero == 1 && flag->precision <= len)
					align (flag->width - (len + minus));
				else if (flag->width - flag->precision + minus > len)
				{
					if (flag->precision < len + minus)
						align (flag->width - (len + minus));
					else if (flag->precision >= len + minus)
						align (flag->width - (flag->precision  + minus));
				}
				else if (flag->width > flag->precision)
				{
					if (flag->width - flag->precision > 0 && flag->precision == len)
					{
						align(flag->width - len);
					}
					else if (flag->precision < len + minus)
					{
						align(flag->width - len);
					}
				}

			}
		}

	}

	if (no_precision_integer(arg, flag))
	{
		if (flag->width >= len && flag->left_align == 0)
			return (flag->width);
		else if (arg == 0 && flag->precision <= 0)
		{
			if ((flag->left_align == 1 && flag->width > 0) && flag->precision == 0)
				return (flag->width);
			else if (flag->precision == 0 && (flag->left_align == 0 || flag->zero == 0))
				return (0);
			else if ((flag->left_align == 1 || flag->zero == 1) && (flag->width == 0 && flag->precision == 0))
				return (0);
		}
	}
	if (flag->precision == flag->width)
		parse_width_integer(arg, flag, minus, len);
	if (flag->width && flag->precision == flag->width)
	{
		if (len >= flag->width)
			return (len + minus);
		else if (len < flag->width)
			return (flag->width + minus);
	}
	else if (flag->precision == flag->width)
		return (len + minus);
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

	arg = va_arg(args, int);
	hex = (size_t)arg;
	len = count_hex(hex);
	if (hex == 0)
		len = 1;
	if (flag->left_align == 1 && flag->precision == -1 && arg != 0)
	{
		ft_puthex(hex);
		if (flag->width > len)
		{
			align(flag->width - len);
			return (flag->width);
		}
		return (len);
	}
	idx = parse_precision_hex(arg, flag, len, hex);
	if (idx >= 0)
		return (idx);
	return (return_x(flag, idx, len));
}

int	printf_X (va_list args, t_flags *flag, int idx)
{
	int		arg;
	size_t	hex;
	int		len;

	arg = va_arg(args, int);
	hex = (size_t)arg;
	len = count_hex(hex);
	if (hex == 0)
		len = 1;
	if (flag->left_align == 1 && flag->precision == -1 && arg != 0)
	{
		ft_putheX(hex);
		if (flag->width > len)
		{
			align(flag->width - len);
			return (flag->width);
		}
		return (len);
	}
	idx = parse_precision_heX(arg, flag, len, hex);
	if (idx >= 0)
		return (idx);
	return (return_x(flag, idx, len));
}
