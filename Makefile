NAME = philo

SRCS = main.c\
		init.c\
		util.c\
		run.c\
		monitor.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
			rm -rf $(OBJS)

fclean: clean
			rm -rf $(NAME)

re: 	fclean $(NAME)

.PHONY:		all clean fclean re
