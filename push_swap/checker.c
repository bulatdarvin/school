/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 01:22:29 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/19 01:22:31 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*get_lst(const int fd, t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd);
	if (tmp == 0)
		return (0);
	ft_lstadd(lst, tmp);
	return (tmp);
}

int		readstr(const int fd, char **line)
{
	int		ret;
	char	a[BUFF_SIZE + 1];
	char	*tmp;

	while ((ret = read(fd, a, BUFF_SIZE)))
	{
		a[ret] = '\0';
		tmp = *line;
		*line = ft_strjoin(*line, a);
		if (*line == NULL)
			return (-1);
		free(tmp);
		if ((ft_strchr(a, '\n')))
			break ;
	}
	return (ret);
}

int		copy(char **line, char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	*line = ft_strnew(i);
	if (!*line)
		return (0);
	ft_strncpy(*line, str, i);
	return (i);
}

void	deletion(char *tmp)
{
	tmp[0] = '\0';
	free(tmp);
}

int		get_next_line(const int fd, char **line)
{
	int				buffer;
	char			*tmp;
	char			buf[BUFF_SIZE];
	static	t_list	*head;
	t_list			*elem;

	if (fd < 0 || BUFF_SIZE <= 0 || line == NULL ||
		(read(fd, buf, 0)) < 0 || !(elem = get_lst(fd, &head)))
		return (-1);
	if (!(readstr(fd, (char**)&(elem->content))) &&
		(!((char*)elem->content)[0] || (char*)elem->content == NULL))
		return (0);
	buffer = copy(line, (char*)elem->content);
	tmp = elem->content;
	if (tmp[buffer])
	{
		elem->content = ft_strdup(&tmp[buffer + 1]);
		deletion(tmp);
	}
	else
		deletion(tmp);
	return (1);
}

int		check_parse(int argc, char **argv, t_stack **stack)
{
	char		**str;
	int			tmp;

	if (argc == 2)
		tmp = parse_str(stack, argv[1]);
	else
		tmp = parse_arr(stack, argv, argc);
	return (tmp);
}

int		act(char *act, t_stack **a, t_stack **b)
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
	else
		return(0);	
	return (1);
}
/*
int		main(int argc, char **argv)
{
	t_stack *a;
	t_stack *b;
	int		i;
	char *tmp;

	a = NULL;
	b = NULL;
	if (argc >= 2)
	{
		i = check_parse(argc, argv, &a);
		while (get_next_line(0, &tmp) > 0)
			{
				if (act(tmp, &a, &b) == 0)
				{
					ft_putendl("Error");
					return (1);
				}
				free(tmp);
			}
		if (lst_sorted(a))
			ft_putendl("OK");
		else
			ft_putendl("KO");
	}
}*/