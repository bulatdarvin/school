/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:00:54 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/03 22:00:05 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*d1;
	unsigned char	*d2;
	size_t			i;

	i = 0;
	d1 = (unsigned char*)s1;
	d2 = (unsigned char*)s2;
	while (d1[i] == d2[i] && d1 != '\0' && i < n)
		i++;
	return (d1[i] - d2[i]);
}
