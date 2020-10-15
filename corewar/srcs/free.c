/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:16:59 by ssilvana          #+#    #+#             */
/*   Updated: 2020/10/15 13:17:00 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	free_all(t_asm *data)
{
	t_label	*label;

	while (data->labels)
	{
		label = data->labels;
		data->labels = data->labels->next;
		free(label->name);
		free(label);
	}
	lines_free(data->lines);
	ft_strdel(&data->name);
	ft_strdel(&data->comment);
	free(data->file_name);
}

void	lines_free(t_line *lines)
{
	if (!lines)
		return ;
	lines_free(lines->next);
	while (lines->nb_params)
	{
		free(lines->params[lines->nb_params - 1]);
		lines->nb_params--;
	}
	free(lines->params);
	free(lines);
}
