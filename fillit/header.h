/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:12:28 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/19 15:12:31 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

typedef struct		s_tet
{
	int				tet_id[8];
	struct s_tet	*next;
	char			c;
}					t_tet;
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# define BUFF_SIZE 8
# define I_PAT (int[8]) {0, 0, 0, 1, 0, 2, 0, 3}
# define IH_PAT (int[8]) {0, 0, 1, 0, 2, 0, 3, 0}
# define O_PAT (int[8]) {0, 0, 1, 0, 0, 1, 1, 1}
# define L_PAT (int[8]) {0, 0, 0, 1, 0, 2, 1, 2}
# define LA_PAT (int[8]) {0, 0, 1, 0, 2, 0, 0, 1}
# define LB_PAT (int[8]) {0, 0, 1, 0, 1, 1, 1, 2}
# define LC_PAT (int[8]) {2, 0, 0, 1, 1, 1, 2, 1}
# define J_PAT (int[8]) {1, 0, 1, 1, 0, 2, 1, 2}
# define JA_PAT (int[8]) {0, 0, 0, 1, 1, 1, 2, 1}
# define JB_PAT (int[8]) {0, 0, 1, 0, 0, 1, 0, 2}
# define JC_PAT (int[8]) {0, 0, 1, 0, 2, 0, 2, 1}
# define T_PAT (int[8]) {0, 0, 1, 0, 2, 0, 1, 1}
# define TA_PAT (int[8]) {1, 0, 0, 1, 1, 1, 1, 2}
# define TB_PAT (int[8]) {1, 0, 0, 1, 1, 1, 2, 1}
# define TC_PAT (int[8]) {0, 0, 0, 1, 1, 1, 0, 2}
# define S_PAT (int[8]) {1, 0, 2, 0, 0, 1, 1, 1}
# define SA_PAT (int[8]) {0, 0, 0, 1, 1, 1, 1, 2}
# define Z_PAT (int[8]) {0, 0, 1, 0, 1, 1, 2, 1}
# define ZA_PAT (int[8]) {1, 0, 0, 1, 1, 1, 0, 2}
t_tet	*readandgroup(int argc, char **argv);
//void	init(char *line, int k, t_tet **elem);
void	ft_push_back(t_tet **begin_list, int *data);
t_tet	*ft_create_elem(int *data);
int 	kolvo(char *line);
int		check(char *line);
char	*readstr(int fd);
#endif