/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_and_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:11:12 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/26 13:11:14 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_tet	*init(char *line, int k)
{
	int		c;
	int		add;
	t_tet	*tmp;
	t_tet	*head;

	add = 0;
	c = 'A';
	if (!(head = (t_tet*)malloc(sizeof(t_tet))))
		return (NULL);
	tmp = head;
	while (k > 0)
	{
		tmp->c = c;
		set_tetris(&tmp, ft_strsub(line, add, 20));
		if (k - 1 != 0)
			if (!(tmp->next = (t_tet*)malloc(sizeof(t_tet))))
				return (NULL);
		tmp = tmp->next;
		k--;
		c++;
		add += 21;
	}
	return (head);
}

char	**create_map(int size)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	if (!(map = (char**)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		if (!(map[i] = (char*)malloc(sizeof(char) * (size + 1))))
		{
			while (i-- > 0)
				free(map[i]);
			ft_memdel((void**)map);
			return (NULL);
		}
		j = -1;
		while (j++ < size - 1)
			map[i][j] = '.';
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	shift(t_tet *elem)
{
	int i;
	int y;
	int x;

	i = 3;
	y = elem->tet_id[1];
	x = elem->tet_id[0];
	while (i < 8)
	{
		if (y > elem->tet_id[i] && i % 2 == 1)
			y = elem->tet_id[i];
		if (x > elem->tet_id[i] && i % 2 == 0)
			x = elem->tet_id[i];
		i = i + 2;
	}
	i = 0;
	while (i < 8)
	{
		if (i % 2 == 0)
			elem->tet_id[i] = elem->tet_id[i] - x;
		else
			elem->tet_id[i] = elem->tet_id[i] - y;
		i++;
	}
}

int		tetris_size(t_tet *elem)
{
	int i;

	i = 0;
	while (elem)
	{
		i++;
		elem = elem->next;
	}
	return (i);
}

int		amount(char *line)
{
	int k;
	int i;

	k = 0;
	i = 0;
	while ((size_t)i < ft_strlen(line))
	{
		while (line[i] && line[i] != '\n' && line[i + 1] != '\n')
		{
			while (line[i] && line[i] != '\n')
				i++;
			i++;
		}
		i++;
		k++;
	}
	return (k);
}
