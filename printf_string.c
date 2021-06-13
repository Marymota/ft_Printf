#include "ft_printf.h"

int	parse_precision_string (char *arg, t_flags *flag)
{
	int	idx;
	int	len;

	idx = 0;
	len = ft_strlen(arg);
	if (flag->precision < len)
		idx = printf_truncate(arg, flag);
	else if (flag->precision >= len)
	{
		if (flag->precision == 0)
			align(flag->width);
		else
			idx = flag->width - len;
		if (flag->left_align == 0)
			if (idx > 0)
				align(idx);
		ft_putstr_fd(arg, 1);
		if (flag->left_align == 1)
			if (idx > 0)
				align(idx);
	}	
	return (idx);
}

int	parse_width_string (char *arg, t_flags *flag)
{
	int	idx;
	int	len;
	int	size;

	idx = 0;
	len = ft_strlen(arg);
	size = flag->width - len;
	if (size > 0)
	{
		idx = size;
		align(size);
	}
	return (idx);
}

int	printf_truncate(char *arg, t_flags *flag)
{
	int	idx;
	int	count_precision;

	idx = 0;
	count_precision = flag->precision;
	if (flag->left_align == 0)
	{
		if (flag->width - flag->precision > 0)
			align(flag->width - flag->precision);
	}
	while (count_precision--)
	{
		ft_putchar_fd(*arg++, 1);
		++idx;
	}
	if (flag->left_align == 1)
	{
		if (flag->width - flag->precision > 0)
			align(flag->width - flag->precision);
	}
	return (idx);
}

int	return_string(t_flags *flag, int idx, int len)
{
	idx = len;
	if (flag->width <= flag->precision)
	{
		if (flag->precision >= 0 && flag->precision <= len)
			idx = flag->precision;
		else if (flag->precision > len && flag->width > len)
			idx = flag->width;
		else if (flag->width < len)
			idx = len;
	}
	else if (flag->width == 0)
	{
		if (flag->precision == -1)
			if (len == -1)
				idx = 0;
	}
	else if (flag->width >= 0)
		if (flag->precision >= 0 || flag->width >= len)
			idx = flag->width;
	return (idx);
}

int	return_null(t_flags *flag)
{
	if (flag->precision <= 0)
	{
		if (flag->width == 0 && flag->precision == 0)
			return (0);
		else if (flag->width > 6 && flag->precision == -1)
			align(flag->width - 6);
	}
	else if (flag->width < flag->precision && flag->precision < 6)
	{
		align(flag->width);
		return (flag->width);
	}
	ft_putstr_fd("(null)", 1);
	if (flag->left_align == 1 && flag->precision > 6)
	{
		align(flag->width - 6);
		return (flag->width);
	}
	if (flag->width > 6)
		return (flag->width);
	return (6);
}
