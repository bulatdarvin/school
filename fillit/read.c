/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:42:34 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/22 17:56:38 by ssilvana         ###   ########.fr       */
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
/*void	solve(t_tet	*elem)
{
	char	**res;
	char	**map;
	int		size;

	
}*/
int	main(int argc, char **argv)
{
	t_tet	*elem;

	elem = check_tetris(argc, argv);
	if (elem == NULL)
		return (0);
	printf("%d", ft_sqrt(10000));
}