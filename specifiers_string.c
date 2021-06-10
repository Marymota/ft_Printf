#include "ft_printf.h"

int	printf_c (va_list args, t_flags *flag, int idx)
{
	int	arg;

	arg = va_arg(args, int);
	if (flag->width > 1 && flag->left_align == 0)
	{
		align(flag->width - 1);
	}
	ft_putchar_fd(arg, 1);
	if (flag->width > 1 && flag->left_align == 1)
	{
		align(flag->width - 1);
	}
	idx = return_char(flag, idx);
	return (idx);
}

int	printf_s (va_list args, t_flags *flag, int idx)
{
	char	*arg; 
	int		len;

	arg = va_arg(args, char *);
	if (arg == NULL)
	{
		if (flag->precision <= 0)
		{
			if (flag->width == 0 && flag->precision == 0)
				return (0);
			else if (flag->width > 6 && flag->precision == -1)
			{
				align(flag->width - 6);
			}
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

	len = ft_strlen(arg);
	if (flag->precision >= 0)
		parse_precision_string(arg, flag);
	else
	{
		if (flag->width > 0 && flag->left_align == 0)
			parse_width_string(arg, flag);
		ft_putstr_fd(arg, 1);
		if (flag->width > 0 && flag->left_align == 1)
			parse_width_string(arg, flag);
	}
	idx = return_string(flag, idx, len);
	return (idx);
}
