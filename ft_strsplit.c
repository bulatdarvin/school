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
		while (*str == c)
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

static void		copy(char *dest, const char *str, int n)
{
	int i;

	i = 0;
	while (str[i] != '\0' && i < n)
	{
		dest[i] = str[i];
		i++;
	}
}

char			**ft_strsplit(char const *str, char c)
{
	int		k;
	int		i;
	int		s;
	char	**tab;

	i = 0;
	s = 0;
	k = word(str, c);
	tab = (char**)malloc(sizeof(char*) * (k + 1));
	while (i < k)
	{
		while (*str == c)
			str++;
		s = size(str, c);
		tab[i] = ft_strnew(s);
		copy(tab[i], str, s);
		tab[i][s] = '\0';
		while (*str != c && *str != '\0')
			str++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
