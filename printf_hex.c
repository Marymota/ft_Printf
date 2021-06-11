#include "ft_printf.h"

int	return_x(t_flags *flag, int idx, int len)
{
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

int	parse_hexadecimal(ssize_t address, t_flags *flag)
{
	int	idx;
	int	len;

	len = count_addr(address) + 2;
	idx = len;
	if (flag->width > (len))
	{
		if (address == 0)
		{
			idx = flag->width;
			align(flag->width - 5);
		}
		else if (flag->width - len > 0)
		{
			idx = flag->width;
			align(flag->width - len);
		}
	}
	return (idx);
}
