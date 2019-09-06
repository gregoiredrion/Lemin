# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdrion <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 13:22:12 by gdrion            #+#    #+#              #
#    Updated: 2019/09/06 22:49:06 by gdrion           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = $(shell find . -type f -name "*.c")
INC = ft_printf.h
OBJ = $(SRC:.c=.o)
CC = gcc

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
