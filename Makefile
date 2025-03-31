# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 17:19:34 by oishchen          #+#    #+#              #
#    Updated: 2025/03/31 15:45:20 by oishchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = my_ft
CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=10
RM = rm -f
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re