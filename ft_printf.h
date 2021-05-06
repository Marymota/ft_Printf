#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct 	flags
{
	int 	left_align;
	int 	asterisk; 
	int 	width;
	int 	precision; 
}				t_flags;

int ft_printf(const char *format, ...);

#endif