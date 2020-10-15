/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:17:05 by ssilvana          #+#    #+#             */
/*   Updated: 2020/10/15 13:17:06 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	*parse_operations(char *line, t_asm *data, t_line *new)
{
	int		i;
	int		op;
	int		start;
	char	*operation;

	i = 0;
	op = -1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	if (!line[i])
		return (0);
	operation = ft_strsub(line, start, i - start);
	while (op++ < 16)
		if (ft_strequ(operation, data->oper[op].name))
		{
			new->nb_params = data->oper[op].nb_params;
			new->command = data->oper[op].op_code;
			free(operation);
			return (line + i);
		}
	free(operation);
	return (0);
}

char	*get_param(char *line, t_line *new, int nb_param)
{
	int		start;
	int		i;
	char	*param;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != SEPARATOR_CHAR
			&& line[i] != ' ' && line[i] != '\t')
		i++;
	if (!(param = ft_strsub(line, start, i - start)))
		return (0);
	if ((param[0] == '%' && parser_digits(param + 1)) ||
		(param[0] == '%' && param[1] == ':' && is_label(param + 2)) ||
		(param[0] == 'r' && ft_atoi(param + 1) > 0 &&
		ft_atoi(param + 1) <= REG_NUMBER) ||
		(param[0] != 'r' && ft_isdigit(param[0])))
	{
		new->params[nb_param] = param;
		return (line + i + 1);
	}
	free(param);
	return (0);
}

char	*parse_params(char *line, t_line *new)
{
	char	*tmp;
	int		nb_param;

	nb_param = 0;
	tmp = line;
	while (nb_param < new->nb_params && *line)
	{
		while (*line && (*line == ' ' || *line == '\t'))
			line++;
		if (!(line = get_param(line, new, nb_param)))
			return (0);
		nb_param++;
	}
	if (nb_param != new->nb_params)
		return (0);
	return (line);
}

int		parse_line_instruct(char *line, t_asm *data, t_line *new)
{
	line = parse_operations(line, data, new);
	if (line == 0)
		return (0);
	line = parse_params(line, new);
	if (line == 0)
		return (0);
	new->line_nb = data->num_lines;
	return (1);
}
