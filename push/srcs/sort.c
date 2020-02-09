/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:07:26 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/23 22:07:28 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			mini_sort(t_main *stack)
{
	int	act;

	if (lst_size(stack->a) == 1)
		return (0);
	if (lst_size(stack->a) == 2)
	{
		if (stack->a->num > stack->a->next->num)
			return (action("sa", &(stack->a), &(stack->b), stack->flag));
		return (0);
	}
	act = 0;
	if (sort_checker(stack->a))
		act += action("sa", &(stack->a), &(stack->b), stack->flag);
	if (stack->a->num != lst_min(stack->a))
	{
		if (stack->a->next->num == lst_min(stack->a))
			act += action("ra", &(stack->a), &(stack->b), stack->flag);
		else
			act += action("rra", &(stack->a), &(stack->b), stack->flag);
	}
	return (act);
}

int			medium_sort(t_main *stack)
{
	int actions;

	actions = 0;
	while (lst_size(stack->a) > 3 && !lst_sorted(stack->a))
	{
		actions += prep_b(stack);
		actions += action("pb", &(stack->a), &(stack->b), stack->flag);
	}
	actions += mini_sort(stack);
	while (stack->b)
	{
		actions += prep_a(stack);
		actions += action("pa", &(stack->a), &(stack->b), stack->flag);
	}
	actions += fix_a(stack);
	return (actions);
}

int			hard_sort(t_main *stack, int num)
{
	int actions;

	actions = 0;
	while (stack->a && has_chunknumber(stack->a, num))
	{
		if (stack->a->num <= num)
		{
			actions += prep_b(stack);
			actions += action("pb", &(stack->a), &(stack->b), stack->flag);
		}
		else
			actions += action("ra", &(stack->a), &(stack->b), stack->flag);
	}
	fix_b(stack);
	return (actions);
}

t_main		sort(t_main stack)
{
	int total;
	int chunks;
	int chunksize;
	int i;

	i = 1;
	total = 0;
	print_to_console(stack.a, stack.b, stack.flag, NULL);
	if (stack.a == NULL)
		ft_exit(stack);
	if (lst_size(stack.a) <= 3)
		total = mini_sort(&stack);
	else if (lst_size(stack.a) <= 40)
		total = medium_sort(&stack);
	else
	{
		chunks = (lst_size(stack.a) <= 100) ? 5 : 11;
		chunksize = (lst_max(stack.a) - lst_min(stack.a)) / chunks;
		while (lst_size(stack.a))
			total += hard_sort(&stack, chunksize * (i++));
		total += go_to_a(&stack);
	}
	if (stack.flag->t)
		ft_printf("Total actions: %d\n", total);
	return (stack);
}
