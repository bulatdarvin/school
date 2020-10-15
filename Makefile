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

NAME = lem-in
CC = gcc
FLAGS = -Wall -Wextra -Werror
OBJECTS_PATH = ./objs/
SRCS_PATH = ./srcs/
LIBFT = ft_printf/libftprintf.a
INCLUDE = include/lem_in.h
INCLUDES = -I ./ft_printf/includes/struct.h -I ./ft_printf/libft/libft.h -I ./include/lem_in.h
DIR_LIBFT = ft_printf

SRCS_NAME = 	lem_in.c\
			ant.c\
			bfs_paths.c\
			bfs.c\
			farm.c\
			free_and_error.c\
			get_paths.c\
			move_ants.c\
			print.c\
			validation_links.c\
			validation_rooms_instruments.c\
			validation_rooms.c
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
