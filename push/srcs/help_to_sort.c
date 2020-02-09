/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_to_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:08:59 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/23 22:09:00 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int		fix_b(t_main *stack)
{
	int			max;
	int			c;
	t_stack		*tmp;

	max = lst_max(stack->b);
	tmp = stack->b;
	c = 0;
	while (tmp)
	{
		if (tmp->num == max)
			break ;
		c++;
		tmp = tmp->next;
	}
	return (go_to_head(stack, c, 'b'));
}

int		fix_a(t_main *stack)
{
	int			max;
	int			c;
	t_stack		*tmp;

	max = lst_min(stack->a);
	tmp = stack->a;
	c = 0;
	while (tmp)
	{
		if (tmp->num == max)
			break ;
		c++;
		tmp = tmp->next;
	}
	return (go_to_head(stack, c, 'a'));
}

int		prep_b(t_main *stack)
{
	t_stack		*tmp;
	int			index;

	tmp = stack->b;
	index = 0;
	if (stack->a->num < lst_min(stack->b) || stack->a->num > lst_max(stack->b))
		return (fix_b(stack));
	while (tmp)
	{
		index++;
		if (tmp->next && stack->a->num < tmp->num
					&& stack->a->num > tmp->next->num)
			break ;
		tmp = tmp->next;
	}
	return (go_to_head(stack, index, 'b'));
}

int		prep_a(t_main *stack)
{
	t_stack		*tmp;
	int			index;

	tmp = stack->a;
	index = 0;
	if (stack->b->num < lst_min(stack->a)
				|| (stack->b)->num > lst_max(stack->a))
		return (fix_a(stack));
	while (tmp)
	{
		index++;
		if (tmp->next && stack->b->num > tmp->num
					&& stack->b->num < tmp->next->num)
			break ;
		tmp = tmp->next;
	}
	return (go_to_head(stack, index, 'a'));
}

int		go_to_a(t_main *stack)
{
	int act;

	act = 0;
	while (stack->b)
		act = action("pa", &(stack->a), &(stack->b), stack->flag);
	return (act);
}
