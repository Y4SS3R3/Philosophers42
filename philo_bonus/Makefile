# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/15 09:50:49 by ymassiou          #+#    #+#              #
#    Updated: 2024/08/15 09:50:49 by ymassiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRC = parsing_utils_bonus.c philo_bonus.c \
		time_bonus.c random_sem.c doctor_bonus.c \
		utils_bonus.c main_bonus.c init_bonus.c utils_bonus2.c

OBJS = $(SRC:%.c=%.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
HEADER = philo_bonus.h

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
