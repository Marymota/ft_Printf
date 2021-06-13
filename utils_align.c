#include "ft_printf.h"

void	align(int len)
{
	while (len--)
		ft_putchar_fd(' ', 1);
}

void	align_integer(int size)
{
	if (size > 0)
		while (size--)
			ft_putchar_fd('0', 1);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s++)
		++i;
	return (i);
}
