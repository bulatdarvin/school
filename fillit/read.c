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

	//tmp = malloc(50);
	tmp = (t_tet*)malloc(sizeof(t_tet));
	if (tmp)
	{
		tmp->tet_id = ft_memalloc(sizeof(data));
		if (tmp->tet_id == 0)
			return (NULL);
		tmp->tet_id = data;
		tmp->next = NULL;
		return (tmp);
	}
	else
	{
		free(tmp);
		return (NULL);
	}
}

void	ft_push_back(t_tet **begin_list, int *data)
{
	t_tet	*list;

	list = *begin_list;
	if (list)
	{
		ft_putchar('a');
		while (list->next)
			list = list->next;
		ft_putchar('a');
		list->next = ft_create_elem(data);
	}
	else
		*begin_list = ft_create_elem(data);

}

void	init(char *line, int k, t_tet **elem)
{
	int i;
	int x;
	int y;
	int t;
	int *a;

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
				}
				x++;
				i++;
			}
			x = 0;
			y++;
			i++;
		}
		ft_putnbr(i);
		ft_push_back(elem, a);		
		y = 0;
		i++;
	}
}

int		warn()
{
	ft_putstr("error");
	return (1);
}
int		main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		k;
	int		*a;
	t_tet	*elem;

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

	init(line, k, &elem);
	ft_putchar('b');
	int i = 0;
	int j = 0;
	while (elem)
	{
		while (i < 8)
		{
			printf("%d\n", elem->tet_id[i]);
			i++;
		}
		elem = elem->next;
	}

	return (0);
}