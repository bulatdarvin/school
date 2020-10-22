/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:17:10 by ssilvana          #+#    #+#             */
/*   Updated: 2020/10/15 13:17:12 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	*handle_label(char *line, t_asm *data)
{
	int		i;
	int		start;
	char	*label;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != LABEL_CHAR
			&& line[i] != ' ' && line[i] != '\t')
	{
		if (wrong_symbol(line[i]))
			return (0);
		i++;
	}
	if (line[i] == LABEL_CHAR)
	{
		label = ft_strsub(line, start, i - start);
		if (!add_label(data, label))
			return (0);
		line += i + 1;
		free(label);
	}
	return (line);
}

int	find_label(t_asm *data, char *to_find)
{
	t_label	*label;

	label = data->labels;
	while (label)
	{
		if (ft_strequ(label->name, to_find))
		{
			if (label->dest)
				return (label->dest->index);
			else
				return (data->size);
		}
		label = label->next;
	}
	return (-1);
}

char	*label_to_num(t_line *line, int direct, int target)
{
	char	*s;
	char	*tmp;

	s = ft_itoa((target - line->index) % MEM_SIZE);
	if (direct)
	{
		tmp = ft_strjoin("%", s);
		free(s);
		return (tmp);
	}
	return (s);
}

int		labels_replace(t_asm *data)
{
	t_line	*line;
	int		i;
	int		target;
	int		direct;

	line = data->lines;
	while (line)
	{
		i = -1;
		while (++i < line->nb_params)
		{
			direct = line->params[i][1] == LABEL_CHAR;
			if (line->params[i][0] == LABEL_CHAR || direct)
			{
				if ((target = find_label(data, line->params[i] + 1 + direct)) == -1)
					return (0);
				free(line->params[i]);
				line->params[i] = label_to_num(line, direct, target);
			}
		}
		line = line->next;
	}
	return (1);
}

int		parser_handle_if_null(t_line *new)
{
	if (new->command == 0)
	{
		lines_free(new);
		return (1);
	}
	else
		return (0);
}