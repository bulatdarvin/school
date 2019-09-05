/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:48:21 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/05 19:20:52 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy(char const *s, char *a, size_t len)
{
	size_t i;

	i = 0;
	while (*s == '\t' || *s == '\n' || *s == ' ')
		s++;
	while (i < len)
	{
		a[i] = *s;
		s++;
		i++;
	}
}

char		*ft_strtrim(char const *s)
{
	size_t		len;
	char		*a;
	const char	*tmp;

	len = 0;
	tmp = s;
	while (*s == '\t' || *s == '\n' || *s == ' ')
		s++;
	while (*s)
	{
		s++;
		len++;
	}
	while (*(s - 1) == '\t' || *(s - 1) == '\n' || *(s - 1) == ' ')
	{
		len--;
		s--;
	}
	a = ft_strnew(len);
	if (a == 0)
		return (NULL);
	ft_copy(tmp, a, len);
	return (a);
}
