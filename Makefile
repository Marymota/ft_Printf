NAME = libftprintf.a
HEADER = ft_printf.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SRCS =	ft_printf.c \
		parse_flags.c \
		specifiers_string.c \
		specifiers_integer.c \
		printf_integer.c \
		printf_string.c \
		printf_unsigned.c \
		printf_address.c \
		printf_hex.c \
		printf_heX.c \
		ft_put.c \
		utils_align.c \
		utils_int.c

OBJS = $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}

bonus: 		all

%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

clean:		
		rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re 