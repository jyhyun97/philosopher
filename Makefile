# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeonhyun <jeonhyun@student.42seoul.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/10 01:05:11 by jeonhyun          #+#    #+#              #
#    Updated: 2021/08/10 01:05:15 by jeonhyun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = init.c\
		util.c\
		main.c\
		run.c\
		do.c
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
