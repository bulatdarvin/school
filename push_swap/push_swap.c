#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>

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
	/*if (t == 'a')
		ft_putendl("pa");
	if (t == 'b')
		ft_putendl("pb");
*/}

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

void		ss(t_stack **a, t_stack **b)
{
	swp(a);
	swp(b);
}

void		rrr(t_stack **a, t_stack **b)
{
	revrot(a);
	revrot(b);
}

void		rr(t_stack **a, t_stack **b)
{
	rot(a);
	rot(b);
}

int			action(char *act, t_stack **a, t_stack **b)
{
	ft_putendl(act);
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
	//lst_print(a);
	return (1);
}

void		lst_del(t_stack *stack)
{
	t_stack *tmp;

	tmp = stack;
	while (stack)
	{
		stack = (stack)->next;
		free(tmp);
		tmp = stack;
	}
	free(stack);
}

int			lst_size(t_stack *stack)
{
	int i;

	i = 0;
	while (stack)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

int			lst_max(t_stack *stack)
{
	int max;

	max = 0;
	if (stack)
		max = stack->num;
	while (stack)
	{
		if (stack->num > max)
			max = stack->num;
		stack = stack->next;
	}
	return (max);
}

int			lst_min(t_stack *stack)
{
	int min;

	min = 0;
	if (stack)
		min = stack->num;
	while (stack)
	{
		if (stack->num < min)
			min = stack->num;
		stack = stack->next;
	}
	return (min);
}

void		lst_print(t_stack *stack)
{
	while (stack)
	{
		ft_putnbr(stack->num);
		ft_putchar('\n');
		stack = stack->next;
	}
	ft_putchar('\n');
}

int			lst_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->num > stack->next->num)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int			check_duplet(t_stack *stack, int num)
{
	while (stack && stack->next)
	{
		if (stack->num == num)
			return (1);
		stack = stack->next;
	}
	return (0);
}

int			ft_isnum(char *str)
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
	return ((!str[i] && digits) ? 1 : 0);
}

void		add(t_stack **stack, int num)
{
	t_stack *tmp;
	t_stack *elem;

	if (!(tmp = ft_memalloc(sizeof(t_stack))))
		return ;
	tmp->num = num;
	tmp->next = NULL;
	if (!(*stack))
	{
		*stack = tmp;
	}
	else
	{
		elem = *stack;
		while (elem->next)
			elem = elem->next;
		elem->next = tmp;
	}
}

int			parse_arr(t_stack **stack, char **str, int argc)
{
	int i;
	int num;

	i = 1;
	while (i < argc)
	{
		if (!ft_isnum(str[i]))
			return (i);
		num = ft_atoi(str[i++]);
		add(stack, num);
		if (check_duplet(*stack, num))
			return (i);
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
			return (i);
		num = ft_atoi(str[i++]);
		add(stack, num);
		if (check_duplet(*stack, num))
			return (i);
	}
	ft_memdeltab(str);
	return (0);
}

t_stack		*parse(int argc, char **argv)
{
	t_stack		*stack;
	char		**str;
	int			tmp;

	stack = NULL;
	if (argc == 2)
		tmp = parse_str(&stack, argv[1]);
	else
		tmp = parse_arr(&stack, argv, argc);
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
	free(head);
	return (0);
}

int			mini_sort(t_main *stack)
{
	if (sort_checker(stack->a))
		action("sa", &(stack->a), &(stack->b));
	if (stack->a->num != lst_min(stack->a))
	{
		if (stack->a->next->num == lst_min(stack->a))
			action("ra", &(stack->a), &(stack->b));
		else
			action("rra", &(stack->a), &(stack->b));
	}
	return (0);
}

int			rot_until(t_main *stack, int c, char t)
{
	int i;

	i = 0;
	if (t == 'a')
		while (i < c)
			i += action("ra", &(stack->a), &(stack->b));
	else
		while (i < c)
			i += action("rb", &(stack->a), &(stack->b));
	return (i);
}

int		revrot_until(t_main *stack, int c, char t)
{
	int i;

	i = 0;
	if (t == 'a')
		while (i < c)
			i += action("rra", &(stack->a), &(stack->b));
	else
		while (i < c)
			i += action("rrb", &(stack->a), &(stack->b));
	return (i);
}

int		go_to_head(t_main *stack, int index, char t)
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
		if (tmp->next && stack->a->num < tmp->num && stack->a->num > tmp->next->num)
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
	if (stack->b->num < lst_min(stack->a) || (stack->b)->num > lst_max(stack->a))
		return (fix_a(stack));
	while (tmp)
	{
		index++;
		if (tmp->next && stack->b->num > tmp->num && stack->b->num < tmp->next->num)
			break ;
		tmp = tmp->next;
	}
	return (go_to_head(stack, index, 'a'));
}

int		medium_sort(t_main *stack)
{
	int actions;

	actions = 0;
	while (lst_size(stack->a) > 3 && !lst_sorted(stack->a))
	{
		actions += prep_b(stack);
		actions += action("pb", &(stack->a), &(stack->b));
	}
	actions += mini_sort(stack);
	while (stack->b)
	{
		actions += prep_a(stack);
		actions += action("pa", &(stack->a), &(stack->b));
	}
	actions += fix_a(stack);
	return (actions);
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

int		hard_sort(t_main *stack, int num)
{
	int actions;

	actions = 0;
	while (stack->a && has_chunknumber(stack->a, num))
	{
		if (stack->a->num <= num)
		{
			actions += prep_b(stack);
			actions += action("pb", &(stack->a), &(stack->b));
		}
		else
			actions += action("ra", &(stack->a), &(stack->b));
	}
	actions += fix_b(stack);
	return (actions);
}

int		go_to_a(t_main *stack)
{
	int act;

	act = 0;
	while (stack->b)
		act += action("pa", &(stack->a), &(stack->b));
	return (act);
}

t_flag		init_flag()
{
	t_flag flag;

	flag.v = 0;
	flag.c = 0;
	return (flag);
}

t_flag		get_flags(int argc, char **argv)
{
	t_flag	flag;
	int		i;

	flag = init_flag();
	i = 1;
	if (argc == 2 && (!ft_isnum(argv[1]) || argv[1][0] != '-'))
	{
		ft_putendl("Error");
	//	return (0);
	}
	if (argv[1][0] == '-')
	{
		while (argv[1][i] && ft_strchr("vc", argv[1][i]))
		{
			if (argv[1][i] == 'v')
				flag.v = 1;
			if (argv[1][i] == 'c')
				flag.c = 1;
		}
		if (argv[1][i])
		{
			ft_putendl("Error");
	//		return (0);
		}
	}
	return (flag);
}

int		main(int argc, char **argv)
{
	t_main		stack;
	int			chunks;
	int			chunksize;
	int			i;
	int			tmp;

	stack.b = NULL;
	system("clear");
	i = 1;
	if (argc > 2)
		stack.flag = get_flags(argc, argv);
	if (argc >= 2)
	{
		stack.a = parse(argc, argv);
		if (lst_size(stack.a) <= 3)
			mini_sort(&stack);
		else if (lst_size(stack.a) <= 50)
			medium_sort(&stack);
		else
		{
			chunks = (lst_size(stack.a) <= 100) ? 5 : 11;
			chunksize = (lst_max(stack.a) - lst_min(stack.a)) / chunks;
			while (lst_size(stack.a))
				hard_sort(&stack, chunksize * (i++));
			go_to_a(&stack);
		}
	}
	lst_del(stack.a);
	lst_del(stack.b);
}
