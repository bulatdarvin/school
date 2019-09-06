/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:57:59 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/06 19:58:02 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_del(void *content, size_t contsize)
{
	(void)contsize;
	free(content);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *list;
	t_list *first;
	t_list *prev;

	list = f(lst);
	if (list == 0)
		return (NULL);
	first = list;
	prev = list;
	lst = lst->next;
	while (lst)
	{
		list = f(lst);
		if (list == 0)
		{
			ft_lstdel(&first, &ft_del);
			return (NULL);
		}
		prev->next = list;
		lst = lst->next;
		prev = list;
	}
	return (first);
}
