#include "ft_printf.h"

int	return_char(t_flags *flag, int idx)
{
	if (flag->width)
		idx = flag->width;
	else
		idx = 1;
	return (idx);
}
