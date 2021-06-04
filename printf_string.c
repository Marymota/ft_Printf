#include "ft_printf.h"

int	parse_precision_string (char *arg, t_flags *flag)
{
	int	idx;
	int	len;
	int	size;

	idx = 0;
	len = ft_strlen(arg);
	size = 0;
	if (flag->precision < len)
		idx = printf_truncate(arg, flag);
	else if (flag->precision >= len && flag->left_align == 1)
	{
		if (flag->precision < flag->width)
			size = flag->width - len;
		else if (flag->precision >= flag->width && flag->width > len)
			size = flag->precision - len;
		else if (flag->precision == 0)
			align(flag->width);
		printf_precision(arg, flag, size);
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

void	printf_precision(char *arg, t_flags *flag, int size)
{
	if (flag->width == 0)
		ft_putstr_fd(arg, 1);
	else if (flag->left_align == 0)
	{
		if (size > 0)
			align(size);
		ft_putstr_fd(arg, 1);
	}
	else if (flag->left_align == 1)
	{
		ft_putstr_fd(arg, 1);
		if (size > 0)
			align(size);
	}
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
		{
			if (len == -1)
				idx = 0;
		}
	}
	else if (flag->width >= 0)
	{
		if (flag->precision >= 0 || flag->width >= len)
			idx = flag->width;
	}
	return (idx);
}
 
  