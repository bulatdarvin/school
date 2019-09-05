/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 15:06:26 by ssilvana          #+#    #+#             */
/*   Updated: 2019/07/09 15:09:56 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	size_t i;
	size_t k;

	i = 0;
	k = ft_strlen(dest);
	while (src[i] != '\0' && i != nb)
	{
		dest[k] = src[i];
		k++;
		i++;
	}
	dest[k] = '\0';
	return (dest);
}
