#include "ft_printf.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n * -1, fd);
	}
	else if (n / 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

void	ft_putunbr(ssize_t n)
{	
	if (n < 0)
		n = 4294967296 + n;
	if (n / 10)
	{
		ft_putnbr_fd(n / 10, 1);
		ft_putchar_fd(n % 10 + '0', 1);
	}
	else
		ft_putchar_fd(n + '0', 1);
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

void	ft_puthex(unsigned int n)
{
	if (n > 15)
	{
		ft_puthex((n / 16));
		ft_puthex((n % 16));
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
