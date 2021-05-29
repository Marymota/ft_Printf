#include "ft_printf.h"

int	uint_size(unsigned int i)
{
	int	idx;

	idx = 0;
	if (i < 10)
		return (1);
	while (i > 9)
	{
		i /= 10;
		++idx;
	}
	if (i)
		++idx;
	return (idx);
}

int	min(int arg)
{
	int	minus;

	minus = 0;
	if (arg < 0)
		minus = 1;
	return (minus);
}

int	int_size(int i)
{
	int	idx;

	idx = 0;
	if (i == -2147483648)
		return (10);
	if (i < 10)
		return (1);
	while (i > 9)
	{
		i /= 10;
		++idx;
	}
	if (i >= 0)
		++idx;
	return (idx);
}

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
