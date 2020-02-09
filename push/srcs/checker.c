/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 01:22:29 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/19 01:22:31 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack		*check_parse(int argc, char **argv, t_main main)
{
	int			tmp;
	t_stack		*stack;

	stack = NULL;
	if (argc == 2)
		tmp = parse_str(&stack, argv[1]);
	else
		tmp = parse_arr(&stack, argv, argc, main);
	return (tmp == 0 ? stack : NULL);
}

int			act(char *act, t_stack **a, t_stack **b)
{
	if (ft_strequ(act, "ra"))
		rot(a);
	else if (ft_strequ(act, "rb"))
		rot(b);
	else if (ft_strequ(act, "rr"))
		rr(a, b);
	else if (ft_strequ(act, "sa"))
		swp(a);
	else if (ft_strequ(act, "sb"))
		swp(b);
	else if (ft_strequ(act, "ss"))
		ss(a, b);
	else if (ft_strequ(act, "rra"))
		revrot(a);
	else if (ft_strequ(act, "rrb"))
		revrot(b);
	else if (ft_strequ(act, "rrr"))
		rrr(a, b);
	else if (ft_strequ(act, "pa"))
		push(b, a);
	else if (ft_strequ(act, "pb"))
		push(a, b);
	else
		return (0);
	return (1);
}

void		checker(t_main stack)
{
	char	*tmp;
	t_stack	*t;

	while (get_next_line(0, &tmp) > 0)
	{
		if (act(tmp, &stack.a, &stack.b) == 0)
			ft_exit(stack);
		free(tmp);
	}
	if (lst_sorted(stack.a))
		ft_putendl("OK");
	else
		ft_putendl("KO");
	t = stack.a;
	while (stack.a)
	{
		stack.a = (stack.a)->next;
		free(t);
		t = stack.a;
	}
	free(stack.b);
	free(stack.flag);
}

int			main(int argc, char **argv)
{
	t_main	stack;

	stack.a = NULL;
	stack.b = NULL;
	stack.flag = init_flag();
	if (argc > 2)
	{
		stack.a = check_parse(argc, argv, stack);
		if (stack.a == NULL)
			ft_exit(stack);
		checker(stack);
	}
	if (argc == 2)
	{
		if (ft_isnum(argv[1]))
			ft_putendl("OK");
		else
			ft_putendl("Error");
	}
	free(stack.flag);
}
