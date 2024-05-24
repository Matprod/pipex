NAME		= pipex
NAME_BONUS 	= pipex_bonus

SRCS 	= mandatory/pipex.c\
			mandatory/utils.c\
			mandatory/ft_split.c\
			mandatory/ft_strjoin.c\

SRCS_BONUS 	= bonus/pipex_bonus.c\
			bonus/utils.c\
			bonus/files_gestion.c\
			bonus/heredoc.c\
			bonus/ft_split.c\
			bonus/ft_strjoin.c\
			bonus/utils2.c\
			bonus/get_next_line_bonus.c\
			bonus/get_next_line_utils_bonus.c\
			
OBJS 		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

HEADER		= -Iincludes

CC      	= gcc
CFLAGS  	= -Wall -Wextra -Werror -g

.c.o:
	@$(CC) ${CFLAGS} ${HEADER} -c $< -o $@


${NAME}: ${OBJS}
	@$(CC) ${OBJS} -o ${NAME}

${NAME_BONUS}: ${OBJS_BONUS}
	@$(CC) ${OBJS_BONUS} -o ${NAME_BONUS}

all: ${NAME} 

bonus: ${NAME_BONUS}

clean:
	@rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	@rm -f ${NAME} ${NAME_BONUS} 

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re