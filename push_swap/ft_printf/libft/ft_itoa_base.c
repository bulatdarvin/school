/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:50:18 by ssilvana          #+#    #+#             */
/*   Updated: 2019/12/13 16:50:20 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		zap(char *a, size_t n, int size, int base)
{
	if (n == 0)
		a[0] = '0';
	while (size > 0 && n > 0)
	{
		if (n % base >= 10)
			a[size - 1] = n % base + 55;
		else		
			a[size - 1] = n % base + '0';
		n = n / base;
		size--;
	}
}

static	char	*sozd(int min, int size, size_t n, int base)
{
	char *a;

	if (min == -1)
	{
		a = ft_strnew(size + 1);
		if (a == 0)
			return (NULL);
		a[0] = '-';
		zap(a, n, size + 1, base);
	}
	else
	{
		a = ft_strnew(size);
		if (a == 0)
			return (NULL);
		zap(a, n, size, base);
	}
	return (a);
}

char			*ft_itoa_base(size_t n, int base)
{
	size_t		num;
	int			size;
	int			min;
	char		*a;

	min = 1;
	size = 1;
	num = n;
	while (n / base != 0)
	{
		size++;
		n = n / base;
	}
	a = sozd(min, size, num, base);
	if (a == 0)
		return (NULL);
	return (a);
}
