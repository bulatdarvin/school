/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:25:19 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/03 21:58:30 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	int i;
	int t;
	int x;
	int q;

	i = 0;
	t = 0;
	x = ft_strlen(to_find);
	while (str[t] != '\0' && t != len)
	{
		while (str[t] != to_find[i] && t != len)
			t++;
		q = t;
		while (str[t] == to_find[i] && to_find[i] != '\0' && t != len)
		{
			i++;
			t++;
		}
		if (t - q == x)
			return ((char*)(str + q));
		else
			i = 0;
	}
	return (NULL);
}
