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

int				ft_atoi(const char *str)
{
	long int	num;
	int			min;

	min = 1;
	num = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\f' || *str == '\v' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		min = check(*str);
		str++;
	}
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str - 48;
		str++;
	}
	if (num > 2147483647 && min == 1)
		return (-2147483648 + num - 2147483648);
	if (num > 2147483648 && min == -1)
		return (2147483647 - num + 2147483648);
	return (num * min);
}
