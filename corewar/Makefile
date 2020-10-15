# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdonnie <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/27 09:22:10 by pdonnie           #+#    #+#              #
#    Updated: 2020/02/27 11:21:11 by pdonnie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm
CC = gcc
FLAGS = -Wall -Wextra -Werror
OBJECTS_PATH = ./objs/
SRCS_PATH = ./srcs/
LIBFT = ft_printf/libftprintf.a
INCLUDE = includes/asm.h
INCLUDES = -I ./ft_printf/includes/struct.h -I ./ft_printf/libft/libft.h -I ./includes/asm.h -I ./includes/op.h
DIR_LIBFT = ft_printf

SRCS_NAME = 	allocation.c\
			file.c\
			free.c\
			instructions.c\
			label.c\
			main.c\
			parse_header.c\
			parser_utils.c\
			parser.c\
			types.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ_NAME = $(SRCS_NAME:%.c=%.o)
OBJECTS = $(addprefix $(OBJECTS_PATH), $(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT) -o $@ $(OBJECTS)

$(LIBFT): FORCE
	@make -C $(DIR_LIBFT)

FORCE:

$(OBJECTS_PATH)%.o: $(SRCS_PATH)%.c $(INCLUDE)
	@mkdir $(OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@/bin/rm -f $(OBJECTS)
	@/bin/rm -rf $(OBJECTS_PATH)
	@/bin/rm -f *.h.gch
	@/bin/rm -f .*.swp
	@make -C $(DIR_LIBFT) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(DIR_LIBFT) fclean

re: fclean all
