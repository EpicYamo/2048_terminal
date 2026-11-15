SRCS = ft_formatspecifier.c ft_if_c.c ft_if_iord.c ft_if_p.c \
		ft_if_pe.c ft_if_s.c ft_if_u.c ft_if_xlower.c ft_putstr.c\
		ft_if_xupper.c ft_printf.c ft_putchar.c ft_strdup.c \
		ft_strlen.c ft_check_edge_cases.c ft_charput_counter.c
OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/,${SRCS:.c=.o})
NAME = libftprintf.a
AR = ar rcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	${AR} ${NAME} $^

${OBJ_DIR}/%.o: %.c ft_printf.h
	mkdir -p ${OBJ_DIR}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJS}
	if [ -d ${OBJ_DIR} ]; then rmdir ${OBJ_DIR}; fi

fclean:
	${RM} ${OBJS}
	if [ -d ${OBJ_DIR} ]; then rmdir ${OBJ_DIR}; fi
	${RM} ${NAME} ${bonus}

re: fclean all

.PHONY : all bonus clean fclean re
