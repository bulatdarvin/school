/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:55:43 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/23 21:55:44 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_free(int fd, t_list *check_list, int status)
{
	t_list	*temp_previous_list;
	t_list	*temp;

	temp = check_list;
	temp_previous_list = check_list;
	while (check_list && (check_list->content_size) != (size_t)fd)
	{
		temp_previous_list = check_list;
		check_list = check_list->next;
	}
	if (!check_list)
		return (-1);
	if (temp_previous_list)
		temp_previous_list->next = check_list->next;
	if (check_list->content)
		free(check_list->content);
	if (!temp && check_list != temp)
		free(check_list);
	if (status == -1)
		return (-1);
	return (0);
}

static int		ft_get_line(char **save, char **line, int ret)
{
	char	*t;
	size_t	i;

	t = (*save);
	i = 0;
	while ((*save) && (*(*save)) != '\n' && (*(*save)) != '\0')
	{
		(*save)++;
		i++;
	}
	if ((*save) && ((**save) == '\n' || (ret == 0)))
	{
		if (((*line) = ft_strsub(t, 0, i)) == NULL)
			return (-1);
		if ((*(*save)) == '\0' || ((*(++(*save))) == '\0'))
			(*save) = NULL;
		else
		{
			if (!((*save) = ft_strsub(t, (i + 1), (ft_strlen(t) - i + 1))))
				return (-1);
		}
		free((void*)t);
		return (1);
	}
	return (0);
}

static int		ft_save_buf(char **save, char *buf, size_t ret)
{
	char	*temp;

	if (ret == 0)
		return (0);
	buf[ret] = '\0';
	if (!(*save))
	{
		if (((*save) = ft_strsub(buf, 0, ret)) == NULL)
			return (-1);
	}
	else
	{
		temp = (*save);
		if (((*save) = ft_strjoin((*save), buf)) == NULL)
			return (-1);
		free((void*)temp);
	}
	return (1);
}

static int		ft_fd(int fd, t_list **list)
{
	t_list			*pnew;

	while ((*list) && (size_t)fd != (*list)->content_size &&
			(*list)->next != NULL)
		(*list) = (*list)->next;
	if (!(*list) || (size_t)fd != ((*list)->content_size))
	{
		if ((pnew = ft_lstnew(NULL, (size_t)fd)) == NULL)
		{
			(*list) = NULL;
			return (-1);
		}
		pnew->content_size = (size_t)fd;
		if (!(*list))
			(*list) = pnew;
		else
		{
			(*list)->next = pnew;
			(*list) = (*list)->next;
		}
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*pl;
	int				r;
	char			buf[BUFF_SIZE + 1];
	int				s;
	t_list			*temp;

	if (fd < 0 || BUFF_SIZE < 1 || !line)
		return (-1);
	temp = (pl) ? pl : NULL;
	if (ft_fd(fd, &pl) == -1)
		return (ft_free(fd, temp, -1));
	s = 2;
	(*line) = NULL;
	while (!*line && (r = read(fd, buf, BUFF_SIZE)) >= 0 && s > 0)
	{
		if ((ft_save_buf((char**)(&(pl->content)), buf, r)) == -1)
			return (ft_free(fd, temp, -1));
		if (r == 0 || (ft_strchr(pl->content, '\n')) != NULL)
			if ((s = ft_get_line((char**)(&(pl->content)), &(*line), r)) == -1)
				return (ft_free(fd, temp, -1));
	}
	if (r < 0)
		return (ft_free(fd, temp, -1));
	pl = (temp) ? temp : pl;
	return (((*line) != NULL) ? 1 : ft_free(fd, temp, 0));
}
