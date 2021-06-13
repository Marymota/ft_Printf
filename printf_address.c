#include "ft_printf.h"

int	count_addr(unsigned long n)
{
	int	idx;

	idx = 0;
	while (n > 0)
	{
		n = n / 16;
		++idx;
	}	
	return (idx);
}

void	ft_putaddr(unsigned long n)
{
	if (n > 15)
	{
		ft_putaddr(n / 16);
		ft_putaddr(n % 16);
	}
	else if (n < 10)
	{
		ft_putchar_fd(n + '0', 1);
	}
	else
	{
		if (n == 10)
			ft_putchar_fd('a', 1);
		else if (n == 11)
			ft_putchar_fd('b', 1);
		else if (n == 12)
			ft_putchar_fd('c', 1);
		else if (n == 13)
			ft_putchar_fd('d', 1);
		else if (n == 14)
			ft_putchar_fd('e', 1);
		else if (n == 15)
			ft_putchar_fd('f', 1);
	}
}

int	parse_hexadecimal(ssize_t address, t_flags *flag)
{
	int	idx;
	int	len;

	len = count_addr(address) + 2;
	idx = len;
	if (flag->width > (len))
	{
		if (address == 0)
		{
			idx = flag->width;
			align(flag->width - 5);
		}
		else if (flag->width - len > 0)
		{
			idx = flag->width;
			align(flag->width - len);
		}
	}
	return (idx);
}
