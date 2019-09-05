/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:19:57 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/05 19:18:41 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*a;

	i = 0;
	a = (char*)ft_memalloc(sizeof(char) * (ft_strlen(s) + 1));
	if (f == 0 && a == 0)
		return (NULL);
	while (i < ft_strlen(s))
	{
		a[i] = f(s[i]);
		i++;
	}
	a[i] = '\0';
	return (a);
}
