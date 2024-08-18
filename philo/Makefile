# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 01:15:23 by ymassiou          #+#    #+#              #
#    Updated: 2024/08/17 23:18:04 by ymassiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = accessors.c \
		doctor.c \
		parsing.c \
		prepare_philos.c \
		get_number.c \
		get_number_utils.c \
		routine.c \
		philo.c \
		clear.c \
		print.c \
		simulation_utils.c \
		forks_utils.c \
		init_philos.c \
		time.c

OBJS = $(SRC:%.c=%.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

