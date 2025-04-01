# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 17:19:34 by oishchen          #+#    #+#              #
#    Updated: 2025/04/01 16:42:26 by oishchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_line
CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=10
RM = rm -f
SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean bonus re