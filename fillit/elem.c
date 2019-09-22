/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 16:54:13 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/20 16:54:15 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

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

int main(int argc, char **argv)
{
	t_tet	*elem;

	elem = readandgroup(argc, argv);
	if (elem == NULL)
		return(0);
	checkpatterns(&elem);
}