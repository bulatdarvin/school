/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:16:30 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/06 14:51:18 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		zap(char *a, long long n, int size)
{
	if (n == 0)
		a[0] = '0';
	while (size > 0 && n > 0)
	{
		a[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
	}
}

static	char	*sozd(int min, int size, long long n)
{
	char *a;

	if (min == -1)
	{
		a = ft_strnew(size + 1);
		if (a == 0)
			return (NULL);
		a[0] = '-';
		zap(a, n, size + 1);
	}
	else
	{
		a = ft_strnew(size);
		if (a == 0)
			return (NULL);
		zap(a, n, size);
	}
	return (a);
}

char			*ft_itoa(int n)
{
	long long	num;
	int			size;
	int			min;
	char		*a;

	min = 1;
	size = 1;
	num = n;
	if (n < 0)
	{
		num = num * (-1);
		min = -1;
	}
	while (n / 10 != 0)
	{
		size++;
		n = n / 10;
	}
	a = sozd(min, size, num);
	if (a == 0)
		return (NULL);
	return (a);
}
