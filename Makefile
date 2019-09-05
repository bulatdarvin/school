# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 20:10:22 by ssilvana          #+#    #+#              #
#    Updated: 2019/09/03 20:14:33 by ssilvana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strnew.c ft_memalloc.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_isalpha.c ft_isalnum.c

INCLUDE = libft.h

all:
	gcc -Wall -Wextra -Werror -I -x $(INCLUDE)
	gcc test.c $(SRC)

