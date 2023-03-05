NAME        := philo
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -fsanitize=thread -g 
SRCS        :=      check.c \
                          main.c \
                          philo_routine.c \
                          utils.c            
OBJS        := $(SRCS:.c=.o)
RM		    := rm -f
.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} 
${NAME}:	${OBJS}
			${CC} ${FLAGS} -o ${NAME} ${OBJS} 
all:		${NAME}
clean:
			${RM} *.o
fclean:		clean
			@ ${RM} ${NAME}
re:			fclean all
.PHONY:		all clean fclean re