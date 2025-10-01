NAME = cube3D

SRCS = srcs/main.c srcs/map.c srcs/utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LIBFT = includes/libft/libft.a

all: $(NAME)
$(NAME): $(OBJS)
	make -C includes/libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

clean:
	rm -f $(OBJS)
	make clean -C includes/libft

fclean: clean
	rm -f $(NAME)
	make fclean -C includes/libft

re: fclean all

.PHONY: all clean fclean re