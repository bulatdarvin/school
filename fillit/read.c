/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:42:34 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/23 18:17:00 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

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

int 	checkone(char *line)
{
	int i;
	int hash;
	int dot;
	int new;

	i = 0;
	hash = 0;
	dot = 0;
	new = 0;
	while (line[i] && i < 20)
	{
		if (line[i] == '#')
			hash++;
		if (line[i] == '.')
			dot++;
		if (line[i] == '\n')
			new++;
		i++;
	}
	if (hash == 4 && dot == 12 && new == 4)
		return (1);
	return (0);
}

int		check(char *line)
{
	int add;

	add = 0;
	while (line[add])
	{
		if (!(checkone(ft_strsub(line, add, 20))))
			return (1);
		add += 19;
		if (line[add] == '\n' && line[add + 1] == '\0')
			return (0);
		if (line[add] == '\n' && line[add + 1] == '\n' &&
				(line[add + 2] == '#' || line[add + 2] == '.'))
			add += 2;
		else
			return (1);
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

int		patterns(int a[8])
{
	if (a == I_PAT || a == IH_PAT || a == O_PAT)
		return (0);
	if (a == L_PAT || a == LA_PAT || a == LB_PAT)
		return (0);
	if (a == LC_PAT || a == J_PAT || a == JA_PAT)
		return (0);
	if (a == JB_PAT || a == JC_PAT || a == T_PAT)
		return (0);
	if (a == TA_PAT || a == TB_PAT || a == TC_PAT)
		return (0);
	if (a == S_PAT || a == SA_PAT || a == Z_PAT)
		return (0);
	if (a == ZA_PAT)
		return (0);
	else
		return (1);
}
int		checkpatterns(t_tet **begin)
{
	t_tet	*tmp;

	tmp = *begin;
	while (tmp)
	{
		shift(tmp);
		if (patterns(tmp->tet_id))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_tet	*warn()
{
	ft_putstr("error");
	return (NULL);
}

t_tet	*check_tetris(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		k;
	t_tet	*elem;

	if (argc != 2)
	{
		ft_putstr("usage: fillit input_file\n");
		return (NULL);	//razobratsia chto takoe usage
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (warn());
	line = readstr(fd);
	if (check(line) == 1 || line[0] == '\0')
		return (warn());
	elem = init(line, kolvo(line));
	if (!checkpatterns(&elem))
		return (warn());
	return (elem);
}

int		tetsize(t_tet *elem)
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

int		ft_sqrt(int a)
{
	float min;
	float max;
	float mid;

	min = 0;
	max = a;
	while (ABS(max - min) > 0.01)
	{
		mid = (max + min) / 2.0;
		if (mid * mid < (float)a)
			min = mid;
		else
			max = mid;
	}
	if ((int)(max - 0.5) == (int)max)
		return ((int)max + 1);
	else
		return ((int)max);
}

void	ft_memdeltab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	//ft_memdel((void**)tab);
}



//                              RESHENIE TETRISA            !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




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
		//	printf("      x: %d   y: %d\n", x, y);
		//	printf("      elemx: %d   elemy: %d\n", elem->tet_id[i], elem->tet_id[i + 1]);
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

int		check_map(t_tet	*elem, char	**map, int size)
{
	int	x;
	int	y;
	int i;

	y = 0;
	i = 0;
	while(y < size)
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
char	**algorit(char **map, int size, t_tet *elem)
{
	int		x;
	int		y;
	char	**tetris;
	int i = 0;

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
			i = 0;
			while (i < 8)
			{
				printf("%d  ", elem->tet_id[i]);
				i++;
			}
			printf("\n");
			if (check_map(elem, map, size))
				tetris = algorit(insert_tetris(map, size, elem),
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


char	**create_map(int size)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	if(!(map = (char**)malloc(sizeof(char*) * (size + 1))))
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

char	**solve(t_tet	*elem)
{
	char	**res;
	char	**map;
	int		size;
	
	size = ft_sqrt(4 * tetsize(elem));
	if(!(map = create_map(size)))
		return (NULL);
	while (!(res = algorit(map, size, elem)))
	{
		printf("size: %d\n", size);
		size++;
		ft_memdeltab(map);
		if(!(map = create_map(size)))
			return (NULL);
	}
	return (res);
}

int	main(int argc, char **argv)
{
	t_tet	*elem;
	char **map;
	int i = 0;

	elem = check_tetris(argc, argv);
	if (elem == NULL)
		return (0);
	map = solve(elem);
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}
