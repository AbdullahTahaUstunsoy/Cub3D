# Program name
NAME = cub3D

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Directories (project specific)
SRC_DIR = srcs
OBJ_DIR = obj
INCLUDES_DIR = includes
LIBFT_DIR = $(INCLUDES_DIR)/libft
GNL_DIR = get_next_line
MLX_DIR = minilibx-linux

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = -L$(MLX_DIR) -lmlx
MLX_FLAGS = -lXext -lX11 -lm -lbsd

# Include paths
INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

# Sources (scan srcs/ recursively)
SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")

# Get Next Line sources (use non-bonus implementation only to avoid duplicate symbols)
GNL_SRCS := $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

# Objects (preserve directory structure under obj/)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
GNL_OBJS := $(patsubst $(GNL_DIR)/%.c,$(OBJ_DIR)/gnl/%.o,$(GNL_SRCS))

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m

.PHONY: all clean fclean re libft mlx

all: $(NAME)

$(LIBFT):
	@echo "$(BLUE)Building libft...$(NC)"
	@make -C $(LIBFT_DIR)

mlx:
	@echo "$(BLUE)Building minilibx...$(NC)"
	@make -C $(MLX_DIR)

$(NAME): $(LIBFT) mlx $(OBJS) $(GNL_OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/gnl/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling GNL $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@find . -name "*.o" -type f -delete
	@make -C $(LIBFT_DIR) clean || true
	@make -C $(MLX_DIR) clean || true

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean || true

re: fclean all
