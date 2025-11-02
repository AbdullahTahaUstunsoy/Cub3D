NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -Iincludes/libft -Iminilibx-linux -Iget_next_line
RM = rm -f

LIBFT_DIR = includes/libft
GNL_DIR = get_next_line
MLX_DIR = minilibx-linux

LIBFT = $(LIBFT_DIR)/libft.a
GNL_SRCS = $(GNL_DIR)/get_next_line.c \
           $(GNL_DIR)/get_next_line_utils.c
MLX_LINK_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

SRCS = srcs/main.c \
srcs/free/free.c \
srcs/key_hooks/key_hooks.c \
srcs/game_operations/init_game.c \
srcs/game_operations/game_loop.c \
srcs/game_operations/game_components.c \
srcs/game_operations/move.c \
srcs/game_operations/ray_engine.c \
srcs/game_operations/draw_pixels.c \
srcs/game_operations/load_textures.c \
srcs/map_operations/map.c \
srcs/map_operations/map_check.c \
srcs/map_operations/map_check_2.c \
srcs/map_operations/map_control.c \
srcs/map_operations/map_flood.c \
srcs/map_operations/map_double_flood.c \
$(GNL_SRCS)


OBJS =$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) mlx
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LINK_FLAGS) -o $(NAME)

mlx:
	@make -C $(MLX_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re mlx libft run
