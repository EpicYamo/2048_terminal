NAME			:= 2048
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
LDLIBS			:= -lncurses
LIBFT			:= libft/libft.a
FT_PRINTF		:= libft/ft_printf/libftprintf.a
LIBFT_SRCS		:= $(filter-out %_bonus.c,$(wildcard libft/*.c))
FT_PRINTF_SRCS	:= $(wildcard libft/ft_printf/*.c)
OBJ_DIR			:= objs
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

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(OBJS) $(FT_PRINTF) $(LIBFT) $(LDLIBS) -o $@

$(LIBFT): $(LIBFT_SRCS) libft/libft.h
	$(MAKE) -C libft

$(FT_PRINTF): $(FT_PRINTF_SRCS) libft/ft_printf/ft_printf.h
	$(MAKE) -C libft/ft_printf

$(OBJ_DIR)/%.o: srcs/%.c srcs/grid.h srcs/game.h srcs/menu.h srcs/scores.h libft/ft_printf/ft_printf.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Isrcs -Ilibft -Ilibft/ft_printf -c $< -o $@

clean:
	rm -f $(OBJS)
	if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi
	$(MAKE) -C libft clean
	$(MAKE) -C libft/ft_printf clean

fclean:
	rm -f $(OBJS)
	if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	$(MAKE) -C libft/ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
