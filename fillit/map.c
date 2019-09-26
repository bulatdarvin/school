/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:07:28 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/26 13:07:29 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**insert_tetris(char **map, int size, t_tet *elem)
{
	int	x;
	int i;
	int	y;

	y = 0;
	i = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (elem->tet_id[i] == x && elem->tet_id[i + 1] == y)
			{
				map[y][x] = elem->c;
				i = i + 2;
			}
			x++;
		}
		y++;
	}
	return (map);
}

void	help_to_insert(t_tet *elem, int x, int y)
{
	int i;

	i = 0;
	shift(elem);
	while (i < 8)
	{
		elem->tet_id[i] = elem->tet_id[i] + x;
		elem->tet_id[i + 1] = elem->tet_id[i + 1] + y;
		i = i + 2;
	}
}

int		check_map(t_tet *elem, char **map, int size)
{
	int	x;
	int	y;
	int i;

	y = 0;
	i = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (elem->tet_id[i] < size && elem->tet_id[i + 1] < size
					&& map[elem->tet_id[i + 1]][elem->tet_id[i]] == '.')
			{
				i = i + 2;
				if (i == 8)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	remove_tetris(char **map, int size, char a)
{
	int x;
	int y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (map[y][x] == a)
				map[y][x] = '.';
			x++;
		}
		y++;
	}
}

void	set_tetris(t_tet **elem, char *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '#')
		{
			(*elem)->tet_id[j] = i % 5;
			j++;
			(*elem)->tet_id[j] = i / 5;
			j++;
		}
		i++;
	}
}
