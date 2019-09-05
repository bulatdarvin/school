/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:45:11 by ssilvana          #+#    #+#             */
/*   Updated: 2019/07/09 23:12:55 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (src[i] != '\0' && i != n)
	{
		dest[i] = src[i];
		i = i + 1;
	}
	if (src[i] == '\0' && i != n)
		while (dest[i] != '\0')
		{
			dest[i] = '\0';
			i++;
		}
	return (dest);
}
