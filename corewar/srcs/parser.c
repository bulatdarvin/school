/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:17:42 by ssilvana          #+#    #+#             */
/*   Updated: 2020/10/15 13:17:43 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		handle_operations(char *line, t_asm *data)
{
	char	*tmp;
	t_line	*new;

	tmp = line;
	line = cut_line(line);
	if (is_comment_or_empty(line))
		return (1);
	new = new_line();
	line = handle_label(line, data);
	if (line == 0)
		return (0);
	if (!parse_line_instruct(line, data, new))
	{
		lines_free(new);
		ft_putendl("AQ");
		return (-1);
	}
	add_line(new, data);
	return (1);
}

int		parse(int fd, t_asm *data)
{
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (handle_operations(line, data) == -1)
		{
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&line);
		data->num_lines++;
	}
	return (1);
}

int		reader(int fd, t_asm *data)
{
	if (!read_name_and_comment(fd, data))
		return (0);
	if (!parse(fd, data))
		return (0);
	return (1);
}
