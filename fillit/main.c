/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:13:44 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/26 22:04:23 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

t_tet	*warn(void)
{
	ft_putstr("error\n");
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_tet	*elem;
	char	**map;
	int		i;

	elem = check_tetris(argc, argv);
	if (elem == NULL)
		return (0);
	map = solve(elem);
	i = 0;
	while (map[i])
	{
		ft_putendl(map[i]);
		i++;
	}
	return (0);
}
