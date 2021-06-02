#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flag;
	int		done;
	int		idx;

	idx = 0;
	va_start(args, format);
	done = parse_format(format, args, &flag, idx);
	va_end (args);
	return (done);
}

int	parse_format(const char *fmt, va_list args, t_flags *flag, int idx)
{
	init(flag);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			++fmt;
			while (flags_check(fmt))
			{
				if (get_flags(fmt, args, flag))
					++fmt;
				else if (ft_isdigit(*fmt))
					fmt += count_digits(fmt, args, flag);
			}
			idx += get_specifier(fmt, args, flag);
			init(flag);
		}
		else
		{
			ft_putchar_fd(*fmt, 1);
			++idx;
		}
		++fmt;
	}
	return (idx);
}

void	init(t_flags *flag)
{
	flag->width = 0;
	flag->left_align = 0;
	flag->asterisk = 0;
	flag->precision = -1;
	flag->zero = 0;
}

int	get_specifier(const char *format, va_list args, t_flags *flag)
{
	int	idx;

	idx = 0;
	if (*format == 'c')
		idx = printf_c(args, flag, idx);
	else if (*format == 's')
		idx = printf_s(args, flag, idx);
	else if (*format == 'p')
		idx = printf_p(args, flag, idx);
	else if (*format == 'd' || *format == 'i')
		idx = printf_d(args, flag, idx);
	else if (*format == 'u')
		idx = printf_u(args, flag, idx);
	else if (*format == 'x')
		idx = printf_x(args, flag, idx);
	else if (*format == 'X')
		idx = printf_X(args, flag, idx);
	else if (*format == '%')
	{
		ft_putchar_fd('%', 1);
		++idx;
	}
	return (idx);
}