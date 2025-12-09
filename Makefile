NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -f

# --- 1. MLX CONFIGURATION ---
MLX_PATH = ./minilibx-linux
MLX_NAME = mlx
MLX_LIB  = $(MLX_PATH)/libmlx.a

# Includes: Look for headers in current dir AND mlx dir
INCLUDES = -I. -I$(MLX_PATH)

# Linker: Look for libs in mlx dir, link mlx, link linux system libs
MLX_FLAGS = -L$(MLX_PATH) -l$(MLX_NAME) -lXext -lX11 -lm -lz
# ----------------------------

SRCS =	main.c \
		core/graphics.c \
		core/inputs.c \
		core/moves.c \
		logic_parsing/check_args.c \
		logic_parsing/fetch_map.c \
		logic_parsing/map_config_fc.c \
		logic_parsing/map_config_tex.c \
		logic_parsing/map_data.c \
		logic_parsing/map_data_helper.c \
		logic_parsing/player_cord.c \
		logic_parsing/final_map.c \
		tools/strings/strings1.c \
		tools/strings/strings2.c \
		tools/strings/strings3.c \
		tools/get_next_line.c \
		tools/garbage_collector/gc_mall.c \
		tools/garbage_collector/gc_mall2.c

OBJS = $(SRCS:.c=.o)

# 2. Add MLX_LIB as a requirement
all: $(MLX_LIB) $(NAME)

# 3. Rule to compile the MLX library if it's missing
$(MLX_LIB):
	@make -C $(MLX_PATH)

# 4. Link everything together (MLX_FLAGS at the end)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) 

# 5. Compile .c to .o with the new includes
%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@make clean -C $(MLX_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re