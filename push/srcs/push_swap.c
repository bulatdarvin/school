/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:22:02 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/23 22:22:04 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	delet(t_main stack)
{
	t_stack *tmp;

	tmp = stack.a;
	while (stack.a)
	{
		stack.a = (stack.a)->next;
		free(tmp);
		tmp = stack.a;
	}
	free(stack.a);
	free(stack.b);
}

int		main(int argc, char **argv)
{
	t_main		stack;

	stack.b = NULL;
	if (argc > 2)
		stack.flag = get_flags(argv);
	else
		stack.flag = init_flag();
	if (argc >= 2)
	{
		stack.a = parse(argc, argv, stack);
		if (stack.a == NULL)
			ft_exit(stack);
		if (argc == 2 && lst_size(stack.a) == 1)
		{
			delet(stack);
			free(stack.flag);
			return (0);
		}
		stack = sort(stack);
		delet(stack);
		free(stack.flag);
	}
	return (0);
}
