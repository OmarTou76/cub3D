CC=gcc

NAME=cub3D

CFLAGS=-Wall -Werror -Wextra

SRCS= src/main.c \
	src/utils/libft.c src/utils/gnl.c src/utils/list_utils.c src/utils/ft_split.c src/utils/libft_additional.c \
	src/parsing/checker.c src/parsing/parse.c \
	src/parsing/map_checker.c src/parsing/fields_checker.c \

OBJS= ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${SRCS} -g

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@
clean: 
	rm ${OBJS}

fclean: clean
	rm ${NAME}

re: fclean all
