NAME = cub3d
NAME_BONUS = cub3d_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

MLX_PATH = ./minilibx-linux
MLX_NAME = mlx
MLX_LIB  = $(MLX_PATH)/libmlx.a

INCLUDES = -Iincludes -I$(MLX_PATH)

MLX_FLAGS = -L$(MLX_PATH) -l$(MLX_NAME) -lXext -lX11 -lm -lz

SRCS =	main.c \
		src/mandatory/graphics.c \
		src/mandatory/drawing.c \
		src/mandatory/raycasting.c \
		src/mandatory/map_data.c \
		src/controls/inputs.c \
		src/controls/moves.c \
		src/controls/moves1.c \
		src/controls/moves_helper.c \
		src/welcome_page.c \
		src/tools/cleanup.c \
		src/logic_parsing/check_args.c \
		src/logic_parsing/fetch_map.c \
		src/logic_parsing/fetch_map_utils.c \
		src/logic_parsing/map_config_fc.c \
		src/logic_parsing/map_config_fc_utils.c \
		src/logic_parsing/map_config_tex.c \
		src/logic_parsing/map_data_helper.c \
		src/logic_parsing/p_cord.c \
		src/logic_parsing/final_map.c \
		src/tools/strings/strings1.c \
		src/tools/strings/strings2.c \
		src/tools/strings/strings3.c \
		src/tools/get_next_line.c \
		src/tools/garbage_collector/gc_mall.c \
		src/tools/garbage_collector/gc_mall2.c

SRCS_BONUS = main.c \
		src/bonus/graphics_bonus.c \
		src/bonus/mouse_bonus.c \
		src/bonus/map_data_bonus.c \
		src/bonus/drawing_bonus.c \
		src/bonus/raycasting_bonus.c \
		src/controls/inputs.c \
		src/controls/moves.c \
		src/controls/moves1.c \
		src/controls/moves_helper.c \
		src/welcome_page.c \
		src/tools/cleanup.c \
		src/logic_parsing/check_args.c \
		src/logic_parsing/fetch_map.c \
		src/logic_parsing/fetch_map_utils.c \
		src/logic_parsing/map_config_fc.c \
		src/logic_parsing/map_config_fc_utils.c \
		src/logic_parsing/map_config_tex.c \
		src/logic_parsing/map_data_helper.c \
		src/logic_parsing/p_cord.c \
		src/logic_parsing/final_map.c \
		src/tools/strings/strings1.c \
		src/tools/strings/strings2.c \
		src/tools/strings/strings3.c \
		src/tools/get_next_line.c \
		src/tools/garbage_collector/gc_mall.c \
		src/tools/garbage_collector/gc_mall2.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) 

bonus: $(MLX_LIB) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(MLX_FLAGS) -o $(NAME_BONUS)

%.o: %.c includes/cub3d.h includes/cub3d_bonus.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@make clean -C $(MLX_PATH)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus