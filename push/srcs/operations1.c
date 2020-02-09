/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:16:05 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/23 22:16:07 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void		push(t_stack **a, t_stack **b)
{
	t_stack *tmp;

	if (*a)
	{
		tmp = (*a)->next;
		(*a)->next = *b;
		*b = *a;
		*a = tmp;
	}
}

void		swp(t_stack **stack)
{
	t_stack *tmp;

	if (*stack && (*stack)->next)
	{
		tmp = (*stack)->next;
		(*stack)->next = tmp->next;
		tmp->next = *stack;
		*stack = tmp;
	}
}

void		rot(t_stack **stack)
{
	t_stack *tmp;
	t_stack *last;

	if (*stack && (*stack)->next)
	{
		last = *stack;
		tmp = (*stack)->next;
		while ((*stack)->next)
			(*stack) = (*stack)->next;
		(*stack)->next = last;
		last->next = NULL;
		*stack = tmp;
	}
}

void		revrot(t_stack **stack)
{
	t_stack *tmp;
	t_stack *last;

	if (*stack && (*stack)->next)
	{
		tmp = *stack;
		while ((*stack)->next->next)
			*stack = (*stack)->next;
		last = (*stack)->next;
		last->next = tmp;
		(*stack)->next = NULL;
		*stack = last;
	}
}
