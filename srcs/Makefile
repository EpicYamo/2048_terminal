NAME		:= 2048
SRCS		:= main.c
OBJS		:= $(SRCS:.c=.o)
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -lncurses
RM			:= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re