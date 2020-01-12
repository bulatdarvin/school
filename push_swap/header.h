#ifndef HEADER_H
# define HEADER_H
#include "ft_printf/includes/struct.h"
# include <stdio.h>
# include <stdlib.h>


typedef struct s_stack
{
	int num;
	struct s_stack *next;
}				t_stack;

typedef struct s_main
{
	struct t_stack *a;
	struct t_stack *b;

}				t_main;
#endif