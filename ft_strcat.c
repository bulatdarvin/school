/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 13:53:30 by ssilvana          #+#    #+#             */
/*   Updated: 2019/07/09 15:09:36 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int i;
	int k;

	i = 0;
	k = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[k] = src[i];
		k++;
		i++;
	}
	dest[k] = '\0';
	return (dest);
}
