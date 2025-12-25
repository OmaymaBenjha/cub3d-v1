NAME = cub3d
NAME_BONUS = cub3d_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

MLX_PATH = ./minilibx-linux
MLX_NAME = mlx
MLX_LIB  = $(MLX_PATH)/libmlx.a

INCLUDES = -I. -I$(MLX_PATH)

MLX_FLAGS = -L$(MLX_PATH) -l$(MLX_NAME) -lXext -lX11 -lm -lz

SRCS =	main.c \
		core/graphics.c \
		core/drawing.c \
		core/raycasting.c \
		core/inputs.c \
		core/moves.c \
		core/moves1.c \
		core/welcome_page.c \
		core/cleanup.c \
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

SRCS_BONUS = main.c \
		core/graphics_bonus.c \
		core/mouse_bonus.c \
		core/drawing.c \
		core/raycasting.c \
		core/inputs.c \
		core/moves.c \
		core/moves1.c \
		core/welcome_page.c \
		core/cleanup.c \
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
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) 

bonus: $(MLX_LIB) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(MLX_FLAGS) -o $(NAME_BONUS)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@make clean -C $(MLX_PATH)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus