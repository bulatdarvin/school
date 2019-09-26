/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:06:10 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/26 14:11:24 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**solve(t_tet *elem)
{
	char	**res;
	char	**map;
	int		size;

	size = ft_sqrt(4 * tetris_size(elem));
	if (!(map = create_map(size)))
		return (NULL);
	while (!(res = algoritm(map, size, elem)))
	{
		size++;
		ft_memdeltab(map);
		if (!(map = create_map(size)))
			return (NULL);
	}
	return (res);
}

char	**algoritm(char **map, int size, t_tet *elem)
{
	int		x;
	int		y;
	char	**tetris;

	y = 0;
	if (elem == NULL)
		return (map);
	tetris = NULL;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			help_to_insert(elem, x, y);
			if (check_map(elem, map, size))
				tetris = algoritm(insert_tetris(map, size, elem),
						size, elem->next);
			if (tetris != NULL)
				return (tetris);
			remove_tetris(map, size, elem->c);
			x++;
		}
		y++;
	}
	return (NULL);
}

int		compare(int a[8], int b[8])
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (1);
}
