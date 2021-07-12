#include "ft_printf.h"

int	printf_c(va_list args, t_flags *flag, int idx)
{
	int	arg;

	arg = va_arg(args, int);
	if (flag->width > 1 && flag->left_align == 0)
		align(flag->width - 1);
	ft_putchar_fd(arg, 1);
	if (flag->width > 1 && flag->left_align == 1)
		align(flag->width - 1);
	if (flag->width)
		idx = flag->width;
	else
		idx = 1;
	return (idx);
}

int	printf_s(va_list args, t_flags *flag, int idx)
{
	char	*arg;
	int		len;

	arg = va_arg(args, char *);
	if (arg == NULL)
		arg = "(null)";
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
