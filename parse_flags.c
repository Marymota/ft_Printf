#include "ft_printf.h"

int	flags_check(const char *fmt)
{
	if (*fmt == '-' || *fmt == '*' || *fmt == '.')
		return (1);
	else if (ft_isdigit(*fmt))
		return (1);
	else
		return (0);
}

int	get_flags(const char *format, va_list args, t_flags *flag)
{
	if (*format == '-')
		flag->left_align = 1;
	else if (*format == '*')
	{
		flag->asterisk = 1;
		parse_asterisk(format, args, flag);
	}
	else if (*format == '.')
		flag->precision = 0;
	else if (*format == '0' && flag->precision == -1)
		flag->zero = 1;
	else
		return (0);
	return (1);
}

void	parse_asterisk(const char *format, va_list args, t_flags *flag)
{
	if (flag->precision >= 0)
		flag->precision = count_width(format, args, flag);
	else
	{
		flag->width = count_width(format, args, flag);
		flag->asterisk = 0;
	}
	if (flag->width < 0)
	{
		flag->width = flag->width * -1;
		flag->left_align = 1;
	}
}

int	count_width(const char *format, va_list args, t_flags *flag)
{
	int	width;

	width = 0;
	if (flag->asterisk == 1)
	{
		flag->asterisk = va_arg(args, int);
		return (flag->asterisk);
	}
	if (ft_isdigit(*format))
	{
		while (ft_isdigit(*format))
		{
			width = width * 10 + (*format - '0');
			++format;
		}
	}
	return (width);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
