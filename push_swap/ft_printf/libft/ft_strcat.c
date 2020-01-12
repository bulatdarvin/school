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

char	*ft_strcat(char *s1, const char *s2)
{
	int i;
	int k;

	i = 0;
	k = ft_strlen(s1);
	while (s2[i] != '\0')
	{
		s1[k] = s2[i];
		k++;
		i++;
	}
	s1[k] = '\0';
	return (s1);
}
