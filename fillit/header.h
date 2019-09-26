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
# define ABS(x) ((x < 0) ? (-x):(x))
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
char	*readstr(int fd);
int 	check_one(char *line);
int		check(char *line);
int 	amount(char *line);
void	set_tetris(t_tet **elem, char *s);
t_tet	*init(char *line, int k);
void	shift(t_tet *elem);
int		patterns(int a[8]);
int		check_patterns(t_tet **begin);
t_tet	*warn();
t_tet	*check_tetris(int argc, char **argv);
int		tetris_size(t_tet *elem);
int		ft_sqrt(int a);
void	ft_memdeltab(char **tab);
char	**insert_tetris(char **map, int size, t_tet *elem);
void	help_to_insert(t_tet *elem, int x, int y);
int		check_map(t_tet	*elem, char	**map, int size);
void	remove_tetris(char **map, int size, char a);
char	**algoritm(char **map, int size, t_tet *elem);
char	**create_map(int size);
char	**solve(t_tet	*elem);
#endif