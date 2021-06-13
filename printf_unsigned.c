#include "ft_printf.h"

void	printf_precision_unsigned(int arg, t_flags *flag, int len)
{
	if (flag->precision > len || flag->width > len)
	{
		if (flag->left_align == 0)
			align(flag->width - len);
		else if (flag->left_align == 1)
			align_integer(flag->precision - len);
	}
	ft_putunbr(arg);
	if (flag->left_align == 1)
	{
		if (flag->precision > len)
			align(flag->width - flag->precision);
		else if (flag->width > len)
			align(flag->width - len);
	}
}

void	printf_width_unsigned(int arg, t_flags *flag, int len)
{
	if (flag->precision == -1 && flag->left_align == 0)
	{
		if (flag->zero == 1)
			align_integer(flag->width - len);
		else if (flag->width > len)
			align(flag->width - len);
		if ((flag->zero == 1) || (flag->width > len))
			ft_putunbr(arg);
	}
	else if (flag->precision >= len && flag->left_align == 0)
	{
		align (flag->width - flag->precision);
		align_integer(flag->precision - len);
		ft_putunbr(arg);
	}
}

int	return_unsigned(ssize_t arg, t_flags *flag, int len)
{
	if (flag->width < len && flag->precision == -1)
	{
		ft_putunbr(arg);
		return (len);
	}
	if (flag->width > flag->precision)
	{
		printf_width_unsigned(arg, flag, len);
		if (flag->left_align == 0)
			if (flag->precision == -1 || flag->precision >= len)
				if (flag->zero == 1 || flag->width > len)
					return (flag->width);
	}
	else if (flag->precision > len)
	{
		align_integer(flag->precision - len);
		ft_putunbr(arg);
		return (flag->precision);
	}
	printf_precision_unsigned(arg, flag, len);
	if (flag->width >= flag->precision && flag->width > len)
		return (flag->width);
	else if (flag->precision > len)
		return (flag->precision);
	return (len);
}
