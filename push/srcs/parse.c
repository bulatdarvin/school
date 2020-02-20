/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:10:17 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/23 22:10:19 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			parse_arr(t_stack **stack, char **str, int argc, t_main main)
{
	int i;
	int num;

	i = has_flag(main.flag) ? 2 : 1;
	while (i < argc)
	{
		if (!ft_isnum(str[i]))
		{
			delet_stack(*stack);
			return (i);
		}
		num = ft_atoi(str[i++]);
		add(stack, num);
		if (check_duplet(*stack, num))
		{
			delet_stack(*stack);
			return (i);
		}
	}
	return (0);
}

int			parse_str(t_stack **stack, char *s)
{
	char	**str;
	int		i;
	int		num;

	str = ft_strsplit(s, ' ');
	i = 0;
	while (str[i])
	{
		if (!ft_isnum(str[i]))
		{
			delet_stack(*stack);
			ft_memdeltab(str);
			return (i);
		}
		num = ft_atoi(str[i++]);
		add(stack, num);
		if (check_duplet(*stack, num))
		{
			delet_stack(*stack);
			ft_memdeltab(str);
			return (i);
		}
	}
	ft_memdeltab(str);
	return (0);
}

t_stack		*parse(int argc, char **argv, t_main main)
{
	t_stack		*stack;
	int			tmp;

	stack = NULL;
	if (argc == 2)
		tmp = parse_str(&stack, argv[1]);
	else
		tmp = parse_arr(&stack, argv, argc, main);
	return (tmp == 0 ? stack : NULL);
}

int			sort_checker(t_stack *a)
{
	t_stack		*head;
	int			i;

	i = 0;
	head = a;
	while (a && a->next)
	{
		if (a->next->num < a->num)
			i++;
		a = a->next;
	}
	if ((i && head->num < a->num) || i == 2)
		return (1);
	return (0);
}
