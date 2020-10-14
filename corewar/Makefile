NAME = asm
HEADER = ./includes/push_swap.h
CC = gcc -Wall -Wextra -Werror -g

OBJECTS_PATH = ./objs/
SRCS_PATH = ./srcs/

SRC = allocation.c \
	file.c \
	free.c \
	instruction.c \
	label.c \
	main.c \
	parse_header.c \
	parser_utils.c \
	parser.c \
	types.c

SRCS = $(addprefix $(SRCS_PATH), $(SRC))

OBJECTS_FILES = $(SRC:.c=.o)
OBJECTS = $(addprefix $(OBJECTS_PATH), $(OBJECTS_FILES))

INCLUDES = -I ./ft_printf/includes/struct.h -I ./ft_printf/libft/libft.h -I $(HEADER)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C printf
	
	$(CC) -o $(NAME) $(OBJECTS) ft_printf/libftprintf.a


$(OBJECTS_PATH)%.o: $(SRCS_PATH)%.c $(HEADER)
	mkdir $(OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	$(CC) -c $< -o $@

clean:
	/bin/rm -f $(OBJECTS) 
	/bin/rm -rf $(OBJECTS_PATH) 
	/bin/rm -f *.h.gch
	/bin/rm -f .*.swp
	make -C printf clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C printf fclean

re: fclean all