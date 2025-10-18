NAME        := cub3d
CC        := gcc #-fsanitize=address
FLAGS    := -Wall -Wextra -Werror -g
LIBFT_DIR := includes/libft
LIBFT     := $(LIBFT_DIR)/libft.a
INCLUDES  := -Imlx -I$(LIBFT_DIR)
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################
SRCS        :=   srcs/main.c srcs/map.c srcs/utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		srcs/map_control.c srcs/key_hooks.c

OBJS        := $(SRCS:.c=.o)
.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}
################################################################################
#                                  Makefile  objs                              #
################################################################################
CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f
UNAME		:=	$(shell uname)

ifeq ($(UNAME), Darwin)
	CFLAGS += -D__APPLE__
else ifeq ($(UNAME), Linux)
	CFLAGS += -D__linux__
else
	$(os not detected)
endif

ifeq ($(UNAME), Darwin)
$(NAME): ${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@ $(MAKE) -C mlx_linux all >/dev/null 2>&1
			@ $(MAKE) -C $(LIBFT_DIR) >/dev/null 2>&1
			@ cp ./mlx_linux/libmlx.a .
		$(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) $(INCLUDES) $(OBJS) -Lmlx_linux -L$(LIBFT_DIR) -lmlx -lft -lm -framework OpenGL -framework AppKit
		@echo "$(GREEN)$(NAME) created\x1b[0m ✔️"
endif
ifeq ($(UNAME), Linux)
$(NAME): ${OBJS}
			@echo "$(GREEN)Linux compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@chmod 777 mlx_linux/configure
			@ $(MAKE) -C mlx_linux all
			@ $(MAKE) -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) -g3 -o $(NAME) $(INCLUDES) $(OBJS) -Imlx_linux -Lmlx_linux -L$(LIBFT_DIR) -lmlx -lft -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
		@echo "$(GREEN)$(NAME) created\x1b[0m ✔️"
endif
all:		${NAME}
ifeq ($(UNAME), Darwin)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif
ifeq ($(UNAME), Linux)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif
ifeq ($(UNAME), Linux)
fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C mlx_linux clean 
			@ $(MAKE) -C $(LIBFT_DIR) fclean
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif
ifeq ($(UNAME), Darwin)
fclean:		clean
			@ ${RM} ${NAME}
			@ rm libmlx.a
			@ $(MAKE) -C $(LIBFT_DIR) fclean >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif
re:			fclean all
.PHONY: 		all clean fclean re