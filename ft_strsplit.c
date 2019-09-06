/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:58:54 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/05 20:58:03 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		word(const char *str, char c)
{
	int k;

	k = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str != '\0')
			k++;
		while (*str != c && *str != '\0')
			str++;
	}
	return (k);
}

static int		size(const char *str, char c)
{
	int i;

	i = 0;
	while (*str != c)
	{
		str++;
		i++;
	}
	return (i);
}

char			**ft_strsplit(char const *str, char c)
{
	int		k;
	int		i;
	int		s;
	char	**tab;

	i = -1;
	s = 0;
	k = word(str, c);
	tab = (char**)malloc(sizeof(char*) * (k + 1));
	if (tab == 0)
		return (NULL);
	while (i++ < k - 1)
	{
		while (*str == c)
			str++;
		s = size(str, c);
		tab[i] = ft_strnew(s);
		if (tab[i] == 0)
			return (NULL);
		ft_strncpy(tab[i], str, s);
		while (*str != c && *str != '\0')
			str++;
	}
	tab[i] = 0;
	return (tab);
}
