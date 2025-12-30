NAME = cub3d
NAME_BONUS = cub3d_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I./minilibx-linux
RM = rm -rf

MLX_PATH = ./minilibx-linux
MLX_NAME = mlx
MLX_LIB  = $(MLX_PATH)/libmlx.a
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
		src/controls/moves_helper1.c \
		src/mandatory/handle_extra_keys.c \
		src/mandatory/welcome_page.c \
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
		src/tools/strings/strings4.c \
		src/tools/get_next_line.c \
		src/tools/garbage_collector/gc_mall.c \
		src/tools/garbage_collector/gc_mall2.c

SRCS_BONUS = main.c \
		src/bonus/graphics_bonus.c \
		src/bonus/mouse_bonus.c \
		src/bonus/map_data_bonus.c \
		src/bonus/drawing_bonus.c \
		src/bonus/raycasting_bonus.c \
		src/bonus/minimap.c \
		src/controls/inputs.c \
		src/controls/moves.c \
		src/controls/moves1.c \
		src/controls/moves_helper.c \
		src/controls/moves_helper1.c \
		src/bonus/handle_extra_keys_bonus.c \
		src/bonus/welcome_page_bonus.c \
		src/tools/cleanup.c \
		src/logic_parsing/check_args.c \
		src/logic_parsing/fetch_map.c \
		src/logic_parsing/fetch_map_utils.c \
		src/logic_parsing/map_config_fc.c \
		src/logic_parsing/map_config_fc_utils.c \
		src/logic_parsing/map_config_tex.c \
		src/logic_parsing/map_data_helper.c \
		src/bonus/p_cord_bonus.c \
		src/logic_parsing/final_map.c \
		src/tools/strings/strings1.c \
		src/tools/strings/strings2.c \
		src/tools/strings/strings3.c \
		src/tools/strings/strings4.c \
		src/tools/get_next_line.c \
		src/tools/garbage_collector/gc_mall.c \
		src/tools/garbage_collector/gc_mall2.c \
		src/logic_parsing/sprite_parsing.c \
		src/bonus/sprite_casting_bonus.c \
		src/bonus/sprite_sorting_bonus.c \
		src/bonus/sprite_casting_utils_bonus.c

OBJ_DIR = obj
OBJ_DIR_BONUS = obj_bonus

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR_BONUS)/, $(SRCS_BONUS:.c=.o))

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(MLX_LIB) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(MLX_FLAGS) -o $(NAME_BONUS)

$(MLX_LIB):
	@make -C $(MLX_PATH)

$(OBJ_DIR)/%.o: %.c includes/cub3d.h includes/cub3d_bonus.h includes/macros.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: %.c includes/cub3d.h includes/cub3d_bonus.h includes/macros.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -D BONUS -c $< -o $@

clean:
	$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@make clean -C $(MLX_PATH)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
