# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makeile                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/12 13:59:15 by ssilvana          #+#    #+#              #
#    Updated: 2019/09/12 13:59:16 by ssilvana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-I.
DEPS = hellomake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all:
	clang -Wall -Wextra -Werror -I libft -o get_next_line.o -c get_next_line.c
	clang -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
	clang -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft
clean:
	/bin/rm -f test_gnl
	/bin/rm -f *.o *.h.gch
re: clean all