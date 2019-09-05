/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:46:24 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/03 21:58:33 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int t;
	int x;
	int q;

	i = 0;
	t = 0;
	x = ft_strlen(to_find);
	while (str[t] != '\0')
	{
		while (str[t] != to_find[i])
			t++;
		q = t;
		while (str[t] == to_find[i] && to_find[i] != '\0')
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
