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

//	printf
int		ft_printf(const char *format, ...);
int		parse_format(const char *fmt, va_list args, t_flags *flag, int idx);
void	init(t_flags *flag);
int		get_specifier(const char *format, va_list args, t_flags *flag);
//	parse_flags
int		flags_check(const char *fmt);
int		get_flags(const char *format, va_list args, t_flags *flag);
void	parse_asterisk(const char *format, va_list args, t_flags *flag);
int		count_width(const char *format, va_list args, t_flags *flag);
int		ft_isdigit(int c);
//	specifiers_string
int		printf_c (va_list args, t_flags *flag, int idx);
int		printf_s (va_list args, t_flags *flag, int idx);
//	specifiers_integer
int		printf_p (va_list args, t_flags *flag, int idx);
int		printf_d (va_list args, t_flags *flag, int idx);
int		printf_u (va_list args, t_flags *flag, int idx);
int		printf_x (va_list args, t_flags *flag, int idx);
int		printf_X (va_list args, t_flags *flag, int idx);
//	printf_string
int		parse_precision_string (char *arg, t_flags *flag);
int		parse_width_string (char *arg, t_flags *flag);
int		printf_truncate(char *arg, t_flags *flag);
int		return_string(t_flags *flag, int idx, int len);
int		return_null(t_flags *flag);
//	printf_integer
void	parse_width_integer(int arg, t_flags *flag, int minus, int len);
int		no_precision_integer(int arg, t_flags *flag);
void	printf_precision_integer(int arg, t_flags *flag, int minus, int len);
void	print_left_align_int(int arg, t_flags *flag, int len, int minus);
int		return_integer(t_flags *flag, int idx, int len, int minus);
//	printf_unsigned
void	printf_precision_unsigned(int arg, t_flags *flag, int len);
void	printf_width_unsigned(int arg, t_flags *flag, int len);
int		return_unsigned(ssize_t arg, t_flags *flag, int len);
//	printf_address
int		count_addr(unsigned long n);
void	ft_putaddr(unsigned long n);
int		parse_hexadecimal(ssize_t address, t_flags *flag);
//	printf_hex
int		count_hex(unsigned int n);
void	ft_puthex(unsigned int n);
int		no_precision_x(int hex, t_flags *flag, int len);
void	parse_precision_hex(int arg, t_flags *flag, int len);
int		return_x(t_flags *flag, int len);
//	printf_heX
void	ft_putheX(unsigned int n);
int		no_precision_X(int hex, t_flags *flag, int len);
void	parse_precision_heX(int arg, t_flags *flag, int len);
//	utils_int
int		uint_size(unsigned int i);
int		int_size(int i);
int		count_digits(const char *format, va_list args, t_flags *flag);
int		min(int arg);
//	utils_align
void	align(int len);
void	align_integer(int size);
size_t	ft_strlen(const char *s);
// fr_put
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putunbr(ssize_t n);

#endif