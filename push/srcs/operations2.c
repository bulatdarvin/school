/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:19:34 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/23 22:19:35 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void		ss(t_stack **a, t_stack **b)
{
	swp(a);
	swp(b);
}

void		rrr(t_stack **a, t_stack **b)
{
	revrot(a);
	revrot(b);
}

void		rr(t_stack **a, t_stack **b)
{
	rot(a);
	rot(b);
}
