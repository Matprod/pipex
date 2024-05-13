PROG	= pipex

SRCS 	= mandatory/pipex.c\
			mandatory/utils.c\
			mandatory/ft_split.c\
			mandatory/ft_strjoin.c\
			
OBJS 	= ${SRCS:.c=.o}
MAIN	= mandatory/pipex.c

HEADER	= -Iincludes

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g

.c.o:
	@$(CC) ${CFLAGS} ${HEADER} -c $< -o $@


all: ${PROG}

${PROG}: ${OBJS}
	@$(CC) ${OBJS} -o ${PROG}


clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${PROG} ${PROG_B}

re: fclean all

.PHONY: all clean fclean re