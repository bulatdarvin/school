/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:09:26 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/26 13:09:28 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_one(char *line)
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
		if (!(check_one(ft_strsub(line, add, 20))))
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

int		check_patterns(t_tet **begin)
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

t_tet	*check_tetris(int argc, char **argv)
{
	char	*line;
	int		fd;
	t_tet	*elem;

	if (argc != 2)
	{
		ft_putstr("usage: fillit input_file\n");
		return (NULL);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (warn());
	line = readstr(fd);
	if (check(line) == 1 || line[0] == '\0')
		return (warn());
	elem = init(line, amount(line));
	if (!check_patterns(&elem))
		return (warn());
	return (elem);
}
