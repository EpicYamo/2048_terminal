NAME			:= 2048
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
LDLIBS			:= -lncurses
FT_PRINTF		:= ft_printf/libftprintf.a
FT_PRINTF_SRCS	:= $(wildcard ft_printf/*.c)
OBJ_DIR			:= objs
HEADERS			:= $(wildcard incs/*.h)
SRCS			:= srcs/main.c \
	srcs/grid.c \
	srcs/grid_layout.c \
	srcs/grid_render.c \
	srcs/game_move.c \
	srcs/game.c \
	srcs/menu.c \
	srcs/scores.c
OBJS			:= $(patsubst srcs/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF)
	$(CC) $(OBJS) $(FT_PRINTF) $(LDLIBS) -o $@

$(FT_PRINTF): $(FT_PRINTF_SRCS) ft_printf/ft_printf.h
	$(MAKE) -C ft_printf

$(OBJ_DIR)/%.o: srcs/%.c $(HEADERS) ft_printf/ft_printf.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincs -Ift_printf -c $< -o $@

clean:
	rm -f $(OBJS)
	if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi
	$(MAKE) -C ft_printf clean

fclean:
	rm -f $(OBJS)
	if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi
	rm -f $(NAME)
	$(MAKE) -C ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
