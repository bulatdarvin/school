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
# define ARG_CNT 2  // 21
# define LENGTH_HH 1
# define LENGTH_H 2
# define LENGTH_LL 4
# define LENGTH_L 3
# define LENGTH_J 6
# define LENGTH_Z 5
# include "libft/libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

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

int		ft_printf(const char *format, ...);
int		handle(char **str, va_list arg, t_flags *flag);
int		call_type(char **str, va_list args, t_flags *flag);
int		ft_pad(t_flags *flag, int size);
int 	handle_length(char **str, t_flags *flag);
void	edit_length(char **str, t_flags *flag, int c, int size);
int		handle_precision(char **str, t_flags *flag, va_list args);
int		handle_width(char **str, t_flags *flag, va_list args);
int		handle_flags(char **str, t_flags *flag);
void	init_flags(t_flags *flag);
int		write_until(char **str, t_flags *flag);
int		ft_write(void *s, int size, t_flags *flag);
int		type_c(va_list arg, t_flags *flag);
int		type_f(va_list arg, t_flags *flag);
int     calc_len(double c, int *size);
void    handle_main(double *nb, char **str, int *i, int mod);
void    handle_point(double nb, char **str, int *i, int precision);
int     float_string(double nb, char **s, int precision);

t_types	types[ARG_CNT] = {
	{'c', type_c}, /*{'C', type_c_upper}, {'s', type_s}, {'S', type_s_upper},
	{'d', type_d}, {'i', type_d}, {'%', type_percentage}, {'p', type_p},
	{'o', type_o}, {'x', type_x}, {'X', type_x_upper}, {'u', type_u},
	{'D', type_d_upper}, {'O', type_o_upper}, {'U', type_u_upper},
	{'a', type_a}, {'A', type_a_upper}, {'b', type_b}, {'n', type_n}*/ {'f', type_f}
};
#endif
