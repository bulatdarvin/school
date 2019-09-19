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
	size_t i;
	size_t t;

	i = 0;
	t = 0;
	if (*to_find == 0)
		return ((char*)str);
	while (str[t] != '\0' && t != len)
	{
		if (str[t] == to_find[0])
		{
			i = 0;
			while (str[t + i] == to_find[i] && to_find[i] && t + i < len)
				i++;
			if (to_find[i] == '\0')
				return ((char*)(str + t));
		}
		t++;
	}
	return (NULL);
}
