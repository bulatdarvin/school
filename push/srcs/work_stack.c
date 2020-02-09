/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:12:04 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/23 22:12:06 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void		add(t_stack **stack, int num)
{
	t_stack *tmp;
	t_stack *elem;

	if (!(tmp = (t_stack *)ft_memalloc(sizeof(t_stack))))
		return ;
	tmp->num = num;
	tmp->next = NULL;
	if (!(*stack))
		*stack = tmp;
	else
	{
		elem = *stack;
		while (elem->next)
			elem = elem->next;
		elem->next = tmp;
	}
}

int			rot_until(t_main *stack, int c, char t)
{
	int i;

	i = 0;
	if (t == 'a')
		while (i < c)
			i += action("ra", &(stack->a), &(stack->b), stack->flag);
	else
		while (i < c)
			i += action("rb", &(stack->a), &(stack->b), stack->flag);
	return (i);
}

int			revrot_until(t_main *stack, int c, char t)
{
	int i;

	i = 0;
	if (t == 'a')
		while (i < c)
			i += action("rra", &(stack->a), &(stack->b), stack->flag);
	else
		while (i < c)
			i += action("rrb", &(stack->a), &(stack->b), stack->flag);
	return (i);
}

int			go_to_head(t_main *stack, int index, char t)
{
	int size;
	int num;

	size = lst_size((t == 'a') ? stack->a : stack->b);
	if (index <= size / 2)
		num = rot_until(stack, index, t);
	else
		num = revrot_until(stack, size - index, t);
	return (num);
}

void		delet_stack(t_stack *stack)
{
	t_stack *tmp;

	tmp = stack;
	while (stack)
	{
		stack = stack->next;
		free(tmp);
		tmp = stack;
	}
	free(stack);
}
