# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/23 22:33:18 by ssilvana          #+#    #+#              #
#    Updated: 2020/01/24 01:17:23 by ssilvana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEP = push_swap
NAMEC = checker
HEADER = ./includes/push_swap.h
CC = gcc -Wall -Wextra -Werror -g

OBJECTS_PATH = ./objs/
SRCS_PATH = ./srcs/

SRCFOR_CHECK = operations1.c operations2.c parse.c checker.c work_stack.c util.c lst.c print_and_flag.c help_to_sort.c
SRCFOR_PUSH = operations1.c operations2.c parse.c print_and_flag.c push_swap.c sort.c util.c work_stack.c help_to_sort.c lst.c
SRCS_CHECK = $(addprefix $(SRCS_PATH), $(SRCFOR_CHECK))
SRCS_PUSH = $(addprefix $(SRCS_PATH), $(SRCFOR_PUSH))

OBJECTS_CHECK_FILES = $(SRCFOR_CHECK:.c=.o)
OBJECTS_CHECK = $(addprefix $(OBJECTS_PATH), $(OBJECTS_CHECK_FILES))

OBJECTS_PUSH_FILES = $(SRCFOR_PUSH:.c=.o)
OBJECTS_PUSH = $(addprefix $(OBJECTS_PATH), $(OBJECTS_PUSH_FILES))



INCLUDES = -I ./printf/includes/struct.h -I ./printf/libft/libft.h -I push_swap.h

.PHONY: all clean fclean re

all: $(NAMEC) $(NAMEP)

$(NAMEC): $(OBJECTS_CHECK)
	@make -C printf
	@$(CC) -o $(NAMEC) $(OBJECTS_CHECK) printf/libftprintf.a

$(NAMEP): $(OBJECTS_PUSH)
	@$(CC) -o $(NAMEP) $(OBJECTS_PUSH) printf/libftprintf.a

$(OBJECTS_PATH)%.o: $(SRCS_PATH)%.c $(HEADER)
	@mkdir $(OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	@$(CC) -c $< -o $@

clean:
	@/bin/rm -f $(OBJECTS) 
	@/bin/rm -rf $(OBJECTS_PATH) 
	@/bin/rm -f *.h.gch
	@/bin/rm -f .*.swp
	@make -C printf clean

fclean: clean
	@/bin/rm -f $(NAMEC) -f $(NAMEP)
	@make -C printf fclean

re: fclean all
