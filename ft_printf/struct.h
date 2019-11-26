/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:13:11 by ssilvana          #+#    #+#             */
/*   Updated: 2019/10/13 18:13:12 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# define BUFF_SIZE 2048
# define ARG_CNT 21
# define LENGTH_HH 1
# define LENGTH_H 2
# define LENGTH_LL 4
# define LENGTH_L 3
# define LENGTH_J 6
# define LENGTH_Z 5
# include "libft/libft.h"
#include <stdio.h>

typedef struct	s_flags
{
	int			hash;
	int			zero;
	int			plus;
	int			minus;
	int			space;
	int			width;
	int			precision;
	char		type;
	char		buffer[BUFF_SIZE];
	int			bytes;
	int			total_bytes;
	int			length_type;
}				t_flags;

typedef struct	s_types
{
	char		name;
	int			(*f)();
}				t_types;
t_types	types[ARG_CNT] = {
	{'c', type_c}, {'C', type_c_upper}, {'s', type_s}, {'S', type_s_upper},
	{'d', type_d}, {'i', type_d}, {'%', type_percentage}, {'p', type_p},
	{'o', type_o}, {'x', type_x}, {'X', type_x_upper}, {'u', type_u},
	{'D', type_d_upper}, {'O', type_o_upper}, {'U', type_u_upper},
	{'a', type_a}, {'A', type_a_upper}, {'f', type_f}, {'F', type_f_upper},
	{'b', type_b}, {'n', type_n}
};
#endif
