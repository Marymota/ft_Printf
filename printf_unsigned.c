#include "ft_printf.h"

int	return_unsigned(ssize_t arg, t_flags *flag, int len)
{
	int	size;

	size = 0;
	if (flag->width < len && flag->precision == -1)
	{
		ft_putunbr(arg);
		return (len);
	}
	else if (flag->width > flag->precision)
	{
		if (flag->precision  == -1)
		{
			if (flag->zero == 1)
			{
				if (flag->width && flag->left_align == 0)
				{
					align_integer(flag->width - len);
					ft_putunbr(arg);
					return (flag->width);
				}
				else 
				{
					ft_putunbr(arg);
					align(flag->width - len);
					return (flag->width);
				}
			}
			else if (flag->width > len && flag->left_align == 0)
			{
				align(flag->width - len);
				ft_putunbr(arg);
				return (flag->width);
			}
			else if (flag->width > len && flag->left_align == 1)
			{
				ft_putunbr(arg);
				align(flag->width - len);
				return (flag->width);
			}

			else 
			ft_putunbr(arg);
			return (len);
		}
		else if (flag->precision >= len && flag->left_align == 0)
		{
			align (flag->width - flag->precision);
			align_integer(flag->precision - len);
			ft_putunbr(arg);
			if (flag->width > flag->precision)
				return (flag->width);
			else 
				return (flag->precision);
		}
		else if (flag->precision >= len && flag->left_align == 1)
		{
			align_integer(flag->precision - len);
			ft_putunbr(arg);
			align (flag->width - flag->precision);
			if (flag->width > flag->precision)
				return (flag->width);
			else 
				return (flag->precision);
		}
	}
	else if (len >= flag->precision && len >= flag->width)
	{
		ft_putunbr(arg);
		return (len);
	}
	else if (flag->precision < len)
	{
		if (flag->width > flag->precision)
		{
			align (flag->width - len);
			ft_putunbr(arg);
		}
		return (flag->width);
	}
	else if (flag->precision > len)
	{
		align_integer(flag->precision - len);
		ft_putunbr(arg);
		return (flag->precision);
	}

	if (flag->precision > len)
		size = flag->width - flag->precision;
	else if (flag->width > len)
		size = flag->width - len;
	if (flag->precision > len || flag->width > len)
		printf_precision_unsigned(flag, size, len);
	ft_putunbr(arg);
	if (flag->left_align == 1)
		if (size > 0)
			align(size);
	if (len >= flag->precision && len >= flag->width)
		return (len);
	else if (flag->width >= flag->precision && flag->width > len)
		return (flag->width);
	if (flag->width < flag->precision)
	{
		if (flag->precision > len)
			return (flag->precision);
		else if (flag->precision < len)
			return (flag->width + len);
	}
	return (len);
}

void	printf_precision_unsigned(t_flags *flag, int size, int len)
{
	if (flag->left_align == 0)
	{
		if (flag->width > flag->precision)
		{
			if (flag->precision == 0 && flag->width > flag->precision)
				align(flag->width - flag->precision - len);
			else if (flag->precision != -1)
			{
				if (flag->width > len)
				{
					size = flag->width - len;
					align(size);
				}

			}
			if (flag->width > flag->precision && flag->precision != -1)
				align_integer(flag->precision - len);
			else if (flag->precision != -1 || flag->left_align)
				align_integer(flag->width - flag->precision - len);
			else
				align_integer(flag->width - len);
		}
		if (flag->width < flag->precision)
			align_integer(flag->precision - len);
	}
	if (flag->left_align == 1)
	{
		if (flag->precision > len)
			align_integer(flag->precision - len);
	}
}

int	no_precision_unsigned(int arg, t_flags *flag, int len)
{
	if (flag->precision < 0)
	{
		if (flag->left_align == 1)
		{
			ft_putunbr(arg);
			align(flag->width - len);
			return (flag->width);
		}
		if (flag->width == 0 && flag->zero == 0)
		{
			ft_putunbr(arg);
			return (1);
		}
		else if (flag->zero == 0)
		{
			align(flag->width - len);
			ft_putunbr(arg);
			return (flag->width);
		}
	}
	return (-1);
}

int	max_int_unsigned(int arg, t_flags *flag, int len)
{

	if (flag->width > len && flag->precision == 0)
	{
		if (flag->zero == 1 && flag->left_align == 0)
		{
			align(flag->width - len);
			ft_putunbr(arg);
			return (flag->width);
		}
	}
	else if (flag->width < len && flag->precision == 0)
	{
		if (flag->zero == 0 || flag->left_align == 0)
		{
			ft_putunbr(arg);
			return (len);
		}
	}
	else if (flag->width < len && flag->precision < len)
	{
			ft_putunbr(arg);
			return (len);
	}
	return (-1);
}

