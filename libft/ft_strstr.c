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

	i = 0;
	t = 0;
	if (*to_find == 0)
		return ((char*)str);
	while (str[t] != '\0')
	{
		if (str[t] == to_find[0])
		{
			i = 0;
			while (str[t + i] == to_find[i] && to_find[i])
				i++;
			if (to_find[i] == '\0')
				return ((char*)(str + t));
		}
		t++;
	}
	return (NULL);
}
