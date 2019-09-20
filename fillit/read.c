/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:42:34 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/19 15:42:36 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

void		ft_lstrev(t_tet **alst)
{
	t_tet	*prev;
	t_tet	*cur;
	t_tet	*next;

	prev = NULL;
	cur = *alst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*alst = prev;
}

char	*readstr(int fd)
{
	int		ret;
	char	a[BUFF_SIZE + 1];
	char	*tmp;
	char	*line;

	line = ft_strdup("");
	while ((ret = read(fd, a, BUFF_SIZE)))
	{
		a[ret] = '\0';
		tmp = line;
		line = ft_strjoin(line, a);
		if (line == NULL)
			return (NULL);
		free(tmp);
	}
	return (line);
}

int		check(char *line)
{
	int i;
	int t;

	i = 0;
	t = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '\n' && line[i + 1] != '\n')
		{
			while (line[i] && line [i] != '\n')
			{
				if (line[i] != '#' && line[i] != '.')
					return(1);
				t++;
				i++;
			}
			i++;
		}
		i++;
		if (t != 16 && t != 0 && line[i] != '\0')
			return (1);
		t = 0;
	}
	return (0);
}

int 	kolvo(char *line)
{
	int k;
	int i;

	k = 0;
	i = 0;
	while (i < ft_strlen(line))
	{
		while (line[i] && line[i] != '\n' && line[i + 1] != '\n')
		{
			while (line[i] && line [i] != '\n')
				i++;
			i++;
		}
		i++;
		k++;
	}
	return (k);
}

t_tet	*ft_create_elem(int *data)
{
	t_tet	*tmp;

	tmp = (t_tet*)malloc(sizeof(t_tet));
	if (tmp)
	{
	//	tmp->tet_id = ft_memalloc(sizeof(data));
	//	if (tmp->tet_id == 0)
	//		return (NULL);
		tmp->tet_id = data;
		tmp->next = NULL;
		return (tmp);
	}
	else
		return (NULL);
}

void	ft_push_back(t_tet **begin_list, int *data)
{
	t_tet	*list;
	static char i = 'a';
	int k = 0;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
		{
			ft_putnbr(k);
			list = list->next;
			k++;
		}
		list->next = ft_create_elem(data);
		list->c = i;
	}
	else
	{
		*begin_list = ft_create_elem(data);
		(*begin_list)->c = i;
	}
	i++;
}

t_tet	*init(char *line, int k, t_tet *elem)
{
	int i;
	int x;
	int y;
	int t;
	int *a;
	t_tet *head;

	i = 0;
	x = 0;
	y = 0;
	t = 0;
	a = ft_memalloc(32);
//	if (a == 0)
//		return (0);
	while (i < ft_strlen(line))
	{
		while (line[i] && line[i] != '\n' && line[i + 1] != '\n')
		{
			while (line[i] && line [i] != '\n')
			{
				if (line[i] == '#')
				{
					a[t++] = x;
					a[t++] = y;
				//	ft_putnbr(a[t - 2]);
				//	ft_putchar(' ');
				//	ft_putnbr(a[t - 1]);
				//	ft_putchar('\n');
				}
				x++;
				i++;
			}
			x = 0;
			y++;
			i++;
		}
	//	ft_putchar('\n');
		ft_push_back(&elem, a);
		//if (i == 20)
		//	head = elem;
		//else
		//	head->next = elem;
		y = 0;
		t = 0;
		i++;
	}
	free(a);
	ft_lstrev(&elem);
	return (elem);
}

int		warn()
{
	ft_putstr("error");
	return (0);
}


int		*shift(int *a)
{
	int i;
	int y;
	int x;

	i = 3;
	y = a[1];
	x = a[0];
	while (i < 8)
	{
		if (y > a[i] && i % 2 == 1)
			y = a[i];
		if (x > a[i] && i % 2 == 0)
			x = a[i];
		i = i + 2;
	}
	i = 0;
	while (i < 8)
	{
		if (i % 2 == 0)
			a[i] = a[i] - x;
		else
			a[i] = a[i] - y;
		i = i + 2;
	}
	return (a);
}

void		checkpatterns(t_tet **begin)
{
	t_tet	*tmp;
	t_tet	*elem;
	int		x;
	int		y;
	int i = 0;

	tmp = *begin;
/*	while (tmp)
	{
		tmp->tet_id = shift(tmp->tet_id);
		tmp = tmp->next;
	}
*/	elem = *begin;
	while (elem)
	{
		while (i < 8)
		{
			printf("%d\n", elem->tet_id[i]);
			i++;
		}
		printf("\n");
		i = 0;
		elem = elem->next;
	}
}

int		main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		k;
	int		*a;
	t_tet	*elem;
	t_tet	*head;

	if (argc != 2)
		return (0);	//razobratsia chto takoe usage
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (warn());
	line = readstr(fd);
	if (check(line) == 1 || line[0] == '\0')
	{
		ft_putstr("error");
		return (0);
	}
	k = kolvo(line);
	head = init(line, k, elem);
	int i = 0;
	while (head)
	{
		while (i < 8)
		{
			printf("%d\n", head->tet_id[i]);
			i++;
		}
		printf("         %c\n\n", head->c);
		i = 0;
		head = head->next;
	}
	return (0);
}
