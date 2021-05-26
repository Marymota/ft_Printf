#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct 	flags
{
	int 	left_align;
	int 	asterisk; 
	int 	width;
	int 	precision; 
	int 	zero;
}				t_flags;

int 	ft_printf(const char *format, ...);
int 	return_char(t_flags *flag, int idx);
int 	return_string(t_flags *flag, int idx, int len);
int 	return_integer(t_flags *flag, int idx, int len, int minus);
int 	return_unsigned(t_flags *flag, int idx, int len);
void	ft_putunbr(ssize_t n);
void	align(int len);
void	align_integer(int size);
int 	is_digit(const char *format);
int 	int_size(int i);
int 	uint_size(unsigned int i);
int 	count_addr(unsigned long n);
int 	count_hex(unsigned int n);
int 	count_width(const char *format, va_list args, t_flags *flag);
int 	count_digits(const char *format, va_list args, t_flags *flag);
void	ft_putchar_fd(char c, int fd);
int 	ft_putstr(char *str);
void	ft_putnbr(int n);
void	ft_putunbr(ssize_t n);
void 	ft_putaddr(unsigned long n);
void 	ft_puthex(unsigned int n);
void 	ft_putheX(unsigned int n);
int 	printf_truncate(char *arg, t_flags *flag);
int 	printf_truncate_integer(int arg, t_flags *flag);
void 	printf_precision(char *arg, t_flags *flag, int size);
int 	printf_truncate_integer(int arg, t_flags *flag);
void 	printf_precision_integer(int arg, t_flags *flag, int size, int minus);
int 	printf_precision_unsigned(ssize_t arg, t_flags *flag, int size, int len);
int 	parse_width_string (char *arg, t_flags *flag);
int 	parse_width_integer (int arg, t_flags *flag, int size);
int 	parse_precision_string (char *arg, t_flags *flag);
int 	parse_hexadecimal(ssize_t address, t_flags *flag);
void 	print_max_int(int arg, t_flags *flag, int len);
int 	printf_c (va_list args, t_flags *flag, int idx);
int 	printf_s (va_list args, t_flags *flag, int idx);
int 	printf_p (va_list args, t_flags *flag, int idx);
int 	printf_d (va_list args, t_flags *flag, int idx);
int 	printf_u (va_list args, t_flags *flag, int idx);
int 	printf_x (va_list args, t_flags *flag, int idx);
int 	printf_X (va_list args, t_flags *flag, int idx);
int 	get_specifier(const char *format, va_list args, t_flags *flag);
void 	parse_asterisk(const char *format, va_list args, t_flags *flag);
int 	get_flags(const char *format, va_list args, t_flags *flag);
void 	init(t_flags *flag);
int 	parse_format(const char *format, va_list args, t_flags *flag, int idx);

#endif