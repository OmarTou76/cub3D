CC=gcc

NAME=cub3D

CFLAGS=-Wall -Werror -Wextra

SRCS= src/main.c src/parsing/checker.c src/utils/libft.c

OBJS= ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${SRCS}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@
clean: 
	rm ${OBJS}

fclean: clean
	rm ${NAME}

re: fclean all