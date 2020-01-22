/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 00:53:21 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/19 00:53:38 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "ft_printf/includes/struct.h"
# include <stdlib.h>
# define BUFF_SIZE 1024
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct	s_stack
{
	int				num;
	int				size;
	struct s_stack	*next;
}				t_stack;

typedef struct	s_flag
{
	int		v;
	int		c;
}				t_flag;

typedef struct	s_main
{
	t_stack *a;
	t_stack *b;
	t_flag	flag;
}				t_main;

void			push(t_stack **a, t_stack **b);
void			swp(t_stack **stack);
void			rot(t_stack **stack);
void			revrot(t_stack **stack);
void			ss(t_stack **a, t_stack **b);
void			rrr(t_stack **a, t_stack **b);
void			rr(t_stack **a, t_stack **b);
int				action(char *act, t_stack **a, t_stack **b);
int				lst_size(t_stack *stack);
void			lst_del(t_stack *stack);
int				lst_max(t_stack *stack);
int				lst_min(t_stack *stack);
void			lst_print(t_stack *stack);
int				lst_sorted(t_stack *stack);
int				check_duplet(t_stack *stack, int num);
int				ft_isnum(char *str);
void			add(t_stack **stack, int num);
int				parse_arr(t_stack **stack, char **str, int argc);
int				parse_str(t_stack **stack, char *s);
t_stack			*parse(int argc, char **argv);
int				sort_checker(t_stack *a);
int				mini_sort(t_main *stack);
int				rot_until(t_main *stack, int c, char t);
int				revrot_until(t_main *stack, int c, char t);
int				go_to_head(t_main *stack, int index, char t);
int				fix_b(t_main *stack);
int				fix_a(t_main *stack);
int				prep_b(t_main *stack);
int				prep_a(t_main *stack);
int				medium_sort(t_main *stack);
int				has_chunknumber(t_stack *stack, int num);
int				hard_sort(t_main *stack, int num);
int				go_to_a(t_main *stack);
// ./a.out 5 4 3 2 1 pb pb sa rra pa ra pa ra
#endif
