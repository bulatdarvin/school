/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:18:14 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/23 22:18:16 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void		print_to_console(t_stack *a, t_stack *b, t_flag *flag, char *act)
{
	if (flag->v)
	{
		system("clear");
		if (act && flag->o)
		{
			if (flag->c)
				ft_putstr("\x1b[31m");
			ft_putendl(act);
		}
		if (flag->c)
			ft_putstr("\x1b[34m");
		ft_putstr("Stack A: ");
		lst_print(a);
		if (flag->c)
			ft_putstr("\x1b[32m");
		ft_putstr("Stack B: ");
		lst_print(b);
		sleep(1);
	}
	if (act)
		ft_putendl(act);
}

int			action(char *act, t_stack **a, t_stack **b, t_flag *flag)
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
	print_to_console(*a, *b, flag, act);
	return (1);
}

t_flag		*init_flag(void)
{
	t_flag *flag;

	flag = malloc(sizeof(t_flag));
	flag->v = 0;
	flag->c = 0;
	flag->t = 0;
	flag->o = 0;
	return (flag);
}

void		help(void)
{
	ft_putendl("Error");
	exit(1);
}

t_flag		*get_flags(char **argv)
{
	t_flag	*flag;
	int		i;

	flag = init_flag();
	i = 1;
	if (ft_isnum(argv[1]) || argv[1][0] != '-')
		return (flag);
	if (argv[1][0] == '-')
	{
		while (argv[1][i] && ft_strchr("vcto", argv[1][i]))
		{
			if (argv[1][i] == 'v')
				flag->v = 1;
			if (argv[1][i] == 'c')
				flag->c = 1;
			if (argv[1][i] == 't')
				flag->t = 1;
			if (argv[1][i] == 'o')
				flag->o = 1;
			i++;
		}
		if (argv[1][i])
			help();
	}
	return (flag);
}
