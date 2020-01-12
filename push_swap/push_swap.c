#include "ft_printf/includes/struct.h"
# include <stdio.h>
# include <stdlib.h>


typedef struct s_stack
{
	int num;
	int size;
	struct s_stack *next;
}				t_stack;

typedef struct s_main
{
	struct t_stack *a;
	struct t_stack *b;

}				t_main;


/*char	*ft_strcatbeg(char *s1, char *s2)
{
	char *tmp;
	int i;

	i = 0;
	tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i] != '\0')
	{
		tmp[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)] != '\0')
	{
		tmp[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
*/
void	push(t_stack **a, t_stack **b)
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

void	swp(t_stack **stack)
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


void	rot(t_stack **stack)
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

void	revrot(t_stack **stack)
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

void	ss(t_stack **a, t_stack **b)
{
	swp(a);
	swp(b);
}

void	rrr(t_stack **a, t_stack **b)
{
	revrot(a);
	revrot(b);
}

void	rr(t_stack **a, t_stack **b)
{
	rot(a);
	rot(b);
}

int		action(char *act, t_stack **a, t_stack **b)
{
	//ft_putendl(act);
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
		push (a, b);
	return (1);
}

int lst_size(t_stack *stack)
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

int lst_max(t_stack *stack)
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

int lst_min(t_stack *stack)
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

int lst_print(t_stack *stack)
{
	while (stack)
	{
		ft_putnbr(stack->num);
		ft_putchar('\n');
		stack = stack->next;
	}
		ft_putchar('\n');
}

int	lst_sorted(t_stack *stack)
{
	while (stack)
	{
		if (stack->num > stack->next->num)
			return (0);
		stack = stack->next;
	}
	return (1);
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
	int 	i;
	int 	digits;

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

void add(t_stack **stack, int num)
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

int	parse_arr(t_stack **stack, char **str, int argc)
{
	int i;
	int num;

	i = 1;
	while (i < argc)
	{
		if (!ft_isnum(str[i]))
			return ;
		num = ft_atoi(str[i++]);
		add(stack, num);
		if (check_duplet(*stack, num))
			return (1);
	}
	return (0);
}

int		parse_str(t_stack **stack, char *s)
{
	char **str;
	int i;
	int num;

	str = ft_strsplit(s, ' ');
	i = 0;
	while (str[i])
	{
		if (!ft_isnum(str[i]))
			return (1);
		num = ft_atoi(str[i++]);
		add(stack, num);
		if (check_duplet(*stack, num))
			return (1);
	}
	ft_memdeltab(str);
	return (0);
}

t_stack *parse(int argc, char **argv)
{
	t_stack *stack;
	char **str;
	int		tmp;

	stack = NULL;
	if (argc == 2)
		tmp = parse_str(&stack, argv[1]);
	else
		tmp = parse_arr(&stack, argv, argc);
	return (tmp == 0 ? stack : NULL);
}

int sort_checker(t_stack *a)
{
	t_stack *head;
	int i;

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

int mini_sort(t_stack **a, t_stack **b)
{
	if (sort_checker(*a))
		action("sa", a, b);
	if ((*a)->num != lst_min(*a))
	{
		if ((*a)->next->num == lst_min(*a))
			action("ra", a, b);
		else
			action ("rra", a, b);
	}
	return (0);
}

int		rot_until(t_stack **stack, int c)
{
	int i;

	i = 0;
	if (*stack)
		while (i < c)
		{
			rot(stack);
			i++;
		}
	return (i);
}

int		revrot_until(t_stack **stack, int c)
{
	int i;

	i = 0;
	if (*stack)
		while (i < c)
		{
			revrot(stack);
			i++;
		}
	return (i);
}

int		go_to_head(t_stack **stack, int index)
{
	int size;
	int num;

	size = lst_size(*stack);
	if (index <= size / 2)
		num = rot_until(stack, index);
	else
		num = revrot_until(stack, size - index);
	return (num);
}

int		fix_b(t_stack **b)
{
	int max;
	int c;
	t_stack *tmp;

	max = lst_max(*b);
	tmp = *b;
	c = 0;
	while (tmp)
	{
		if (tmp->num == max)
			break ;
		c++;
		tmp = tmp->next;
	}
	return (go_to_head(b, c));
}

int		fix_a(t_stack **a)
{
	int max;
	int c;
	t_stack *tmp;

	max = lst_min(*a);
	tmp = *a;
	c = 0;
	while (tmp)
	{
		if (tmp->num == max)
			break ;
		c++;
		tmp = tmp->next;
	}
	return (go_to_head(a, c));
}

int		prep_b(t_stack **a, t_stack **b)
{
	t_stack *tmp;
	int index;

	tmp = *b;
	index = 0;
	if ((*a)->num < lst_min(*b) || (*a)->num > lst_max(*b))
		return (fix_b(b));
	while (tmp)
	{
		index++;
		if (tmp->next && (*a)->num < tmp->num && (*a)->num > tmp->next->num)
			break ;
		tmp = tmp->next;
	}
	return (go_to_head(b, index));
}

int		prep_a(t_stack **a, t_stack **b)
{
	t_stack *tmp;
	int index;

	tmp = *a;
	index = 0;
	if ((*b)->num < lst_min(*a) || (*b)->num > lst_max(*a))
		return (fix_a(a));
	while (tmp)
	{
		index++;
		if (tmp->next && (*b)->num > tmp->num && (*b)->num < tmp->next->num)
			break ;
		tmp =tmp->next;
	}
	return (go_to_head(a, index));
}

int		medium_sort(t_stack **a, t_stack **b)
{
	int actions;

	actions = 0;
	while (lst_size(*a) > 3 && !lst_sorted(*a))
	{
		actions += prep_b(a, b);
		actions += action("pb", a, b);
	}
	actions += mini_sort(a, b);
	while (*b)
	{
		actions += prep_a(a, b);
		actions += action("pa", a, b);
		
	}
	actions += fix_a(a);
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

int		hard_sort(t_stack **a, t_stack **b, int num)
{
	int actions;

	actions = 0;
	while (*a && has_chunknumber(*a, num))
	{
		if ((*a)->num <= num)
		{
			actions += prep_b(a, b);
			actions += action("pb", a, b);
		}
		else
			actions += action("ra", a, b);
	}
	actions += fix_b(b);
}

int		go_to_a(t_stack **a, t_stack **b)
{
	int act;

	act = 0;
	while (*b)
		act += action("pa", a, b);
	return (act);
}

int		main(int argc, char **argv)
{
	t_stack *a;
	t_stack *b;
	int actions;
	int chunks;
	int chunksize;
	int i;

	b = NULL;
	i = 1;
	if (argc >=2)
	{
		a = parse(argc, argv);
		if (lst_size(a) <= 3)
			mini_sort(&a, &b);
		else if (lst_size(a) <= 50)
			medium_sort(&a, &b);
		else
		{
			chunks = (lst_size(a) <= 100) ? 5 : 11;
			chunksize = (lst_max(a) - lst_min(a)) / chunks;
			while (lst_size(a))
			{
				hard_sort(&a, &b, chunksize * i);
				i++;
			}
			go_to_a(&a, &b);
		}
	}
}