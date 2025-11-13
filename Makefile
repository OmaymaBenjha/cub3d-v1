NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror  
RM = rm -f

SRCS =	main.c \
		logic_parsing/check_args.c \
		logic_parsing/fetch_map.c \
		logic_parsing/map_config_fc.c \
		logic_parsing/map_config_tex.c \
		tools/strings/strings1.c \
		tools/strings/strings2.c \
		tools/strings/strings3.c \
		tools/get_next_line.c




OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) 

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
