#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_flags
{
	int	left_align;
	int	asterisk;
	int	width;
	int	precision;
	int	zero;
}				t_flags;

int		ft_printf(const char *format, ...);
void	init(t_flags *flag);
void	parse_asterisk(const char *format, va_list args, t_flags *flag);
int		get_specifier(const char *format, va_list args, t_flags *flag);
int		get_flags(const char *format, va_list args, t_flags *flag);
int		flags_check(const char *fmt);
int		parse_format(const char *fmt, va_list args, t_flags *flag, int idx);
int		printf_c (va_list args, t_flags *flag, int idx);
int		printf_s (va_list args, t_flags *flag, int idx);
int		printf_p (va_list args, t_flags *flag, int idx);
int		printf_d (va_list args, t_flags *flag, int idx);
int		printf_u (va_list args, t_flags *flag, int idx);
int		printf_x (va_list args, t_flags *flag, int idx);
int		printf_X (va_list args, t_flags *flag, int idx);
void	printf_precision(char *arg, t_flags *flag, int size);
int		return_char(t_flags *flag, int idx);
int		return_string(t_flags *flag, int idx, int len);
int		parse_width_string (char *arg, t_flags *flag);
int		parse_precision_string (char *arg, t_flags *flag);
int		printf_truncate(char *arg, t_flags *flag);
void	printf_precision_integer(int arg, t_flags *flag, int minus, int len);
void	align_integer(int size);
void	parse_width_integer(int arg, t_flags *flag, int minus, int len);
void	print_left_align_int(int arg, t_flags *flag, int len, int minus);
int		no_precision_integer(int arg, t_flags *flag);
int		return_integer(t_flags *flag, int idx, int len, int minus);
int		int_size(int i);
void	printf_precision_unsigned(t_flags *flag, int size, int len);
int		return_unsigned(ssize_t arg, t_flags *flag, int len);
int		no_precision_unsigned(int arg, t_flags *flag, int len);
int		max_int_unsigned(int arg, t_flags *flag, int len);
int		parse_unsigned(int arg, t_flags *flag, int len, int idx);
int		uint_size(unsigned int i);
void	align_hex(t_flags *flag, int len, int hex);
void	align_heX(t_flags *flag, int len, int hex);
void	ft_puthex(unsigned int n);
void	ft_putheX(unsigned int n);
int		return_x(t_flags *flag, int idx, int len);
int		zero_arg_hex(int arg, t_flags *flag, int len, int hex);
int		zero_arg_heX(int arg, t_flags *flag, int len, int hex);
int		parse_precision_hex(int arg, t_flags *flag, int len, int hex);
int		parse_precision_heX(int arg, t_flags *flag, int len, int hex);
int		parse_hexadecimal(ssize_t address, t_flags *flag);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_putunbr(ssize_t n);
void	ft_putaddr(unsigned long n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	align(int len);
int		min(int arg);
int		count_addr(unsigned long n);
int		count_hex(unsigned int n);
int		count_width(const char *format, va_list args, t_flags *flag);
int		count_digits(const char *format, va_list args, t_flags *flag);

#endif