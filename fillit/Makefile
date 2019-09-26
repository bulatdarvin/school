# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 20:10:22 by ssilvana          #+#    #+#              #
#    Updated: 2019/09/26 13:18:11 by ssilvana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FUNC_NAME = ft_memset \
	  ft_bzero \
	  ft_memcpy \
	  ft_memccpy \
	  ft_memmove \
	  ft_memchr \
	  ft_memcmp \
	  ft_strlen \
	  ft_strdup \
	  ft_strnew \
	  ft_memalloc \
	  ft_strcpy \
	  ft_strncpy \
	  ft_strcat \
	  ft_strncat \
	  ft_strchr \
	  ft_strrchr \
	  ft_strstr \
	  ft_strnstr \
	  ft_strcmp \
	  ft_strncmp \
	  ft_isalpha \
	  ft_isalnum \
	  ft_memdel \
	  ft_strdel \
	  ft_strclr \
	  ft_striter \
	  ft_striteri \
	  ft_strmap \
	  ft_strmapi \
	  ft_strequ \
	  ft_strnequ \
	  ft_strsub \
	  ft_strjoin \
	  ft_putchar \
	  ft_putstr \
	  ft_putendl \
	  ft_putnbr \
	  ft_isdigit \
	  ft_isascii \
	  ft_isprint \
	  ft_toupper \
	  ft_tolower \
	  ft_atoi \
	  ft_strlcat \
	  ft_strtrim \
	  ft_strsplit \
	  ft_itoa \
	  ft_putchar_fd \
	  ft_putstr_fd \
	  ft_putendl_fd \
	  ft_putnbr_fd \
	  ft_lstnew \
	  ft_lstdelone \
	  ft_lstdel \
	  ft_lstadd \
	  ft_lstiter \
	  ft_lstmap \
	  ft_sqrt \
	  ft_memdeltab


SRC = $(addsuffix .c, $(FUNC_NAME))

FUNCTION = $(addsuffix .o, $(FUNC_NAME))

INCLUDE = libft.h

all: $(NAME)

$(FUNCTION): %.o: %.c

$(NAME): $(FUNCTION) #compile
		@gcc -Wall -Wextra -Werror -c $(SRC) -I $(INCLUDE)
		@ar rc $(NAME) $(FUNCTION)
	
clean:
		@/bin/rm -f $(FUNCTION)
		@/bin/rm -f *.h.gch
		@/bin/rm -f .*.swp

fclean: clean
		@/bin/rm -f $(NAME)

re: fclean all
