/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:57:35 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/05 17:07:21 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		check(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

static	int		special(unsigned long num, int min)
{
	if (num > 2147483647 && min == 1)
		return (-2147483648 + num - 2147483648);
	if (num > 2147483648 && min == -1)
		return (2147483647 - num + 2147483648);
	else
		return (num);
}

static	int		space(char str)
{
	if (str == ' ' || str == '\n' || str == '\t' ||
			str == '\f' || str == '\v' || str == '\r')
		return (1);
	else
		return (0);
}

int				ft_atoi(const char *str)
{
	long long int	num;
	int				min;
	long long int	t;

	min = 1;
	num = 0;
	while (space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		min = check(*str);
		str++;
	}
	while (ft_isdigit(*str))
	{
		t = num * 10 + *str - 48;
		if (t / 10 != num && min == 1)
			return (-1);
		if (t / 10 != num && min == -1)
			return (0);
		num = num * 10 + *str - 48;
		str++;
	}
	num = special(num, min);
	return (num * min);
}
