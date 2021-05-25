NAME = libftprintf.a
HEADER = ft_printf.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft
LIBFT_LIB = libft.a
AR = ar rcs

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $^

bonus: 		all

%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

clean:		
		rm -f $(OBJS)
		make fclean -C $(LIBFT)

fclean:		clean
			rm -f $(NAME)
			make fclean -C $(LIBFT)

re:			fclean all

.PHONY: 	all clean fclean re