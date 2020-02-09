/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:12:50 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/23 22:12:51 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int		has_flag(t_flag *flag)
{
	if (!flag->c && !flag->v && !flag->t && !flag->o)
		return (0);
	return (1);
}

int		has_chunknumber(t_stack *stack, int num)
{
	while (stack)
	{
		if (stack->num <= num)
			return (1);
		stack = stack->next;
	}
	return (0);
}

void	ft_exit(t_main stack)
{
	free(stack.flag);
	ft_putendl("Error");
	exit(1);
}

int		check_duplet(t_stack *stack, int num)
{
	while (stack && stack->next)
	{
		if (stack->num == num)
			return (1);
		stack = stack->next;
	}
	return (0);
}

int		ft_isnum(char *str)
{
	int		i;
	int		digits;

	i = 0;
	digits = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		i++;
		digits++;
	}
	if (digits >= 10)
		return (0);
	return ((!str[i] && digits) ? 1 : 0);
}
