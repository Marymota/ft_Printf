#include "ft_printf.h"

void	align_hex(t_flags *flag, int len, int hex)
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
	ft_puthex(hex);
	if (flag->left_align == 1)
	{
		if (flag->precision >= len)
			align(flag->width - flag->precision);
		else if (flag->precision < len)
			align (flag->width - len);
	}
} 

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

int	parse_precision_hex(int arg, t_flags *flag, int len, int hex)
{
	int	idx;
 
	idx = len;
	arg = hex;

	if (flag->left_align == 1)
	{
		if (flag->precision >= len)
		{
			align_integer(flag->precision - len);
		}
		ft_puthex(arg);
		if (flag->precision >= 0 && flag->width > flag->precision)
		{
			if (flag->precision > len)
			{
				if (flag->width - flag->precision > 0)
					align(flag->width - flag->precision);
			}
			else if (flag->precision <= len)
			{
			 	if (flag->width - len > 0)
					align(flag->width - len);
			}
		}
		return (flag->precision);
	}
	else if (flag->width >= flag->precision)
	{
		if (flag->width > len)
		{
			if (flag->precision > len)
			{
				align (flag->width - flag->precision);
				align_integer(flag->precision - len);
			}
			else 
			{
				align (flag->width - len);
			}
			ft_puthex(arg);
			return (flag->width);
		}
		ft_puthex(arg);
		return (len);
	}
	else if (flag->width < flag->precision)
	{
		if (flag->precision > len)
			align_integer(flag->precision - len);
		ft_puthex(hex);
		return (flag->precision);
	}
	else if (flag->precision < len && flag->width >= 0)
	{
		ft_puthex(arg);
		return (idx);
	}
	else 
		align_hex(flag, len, hex);
	return (-1);
}

int	parse_hexadecimal(ssize_t address, t_flags *flag)
{
	int	idx;
	int	len;


	len = count_addr(address) + 2;
	idx = len;

	if (flag->width == 0 && flag->precision == -1)
	{
		idx = len;
	}
	else if (flag->width > (len))
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
 