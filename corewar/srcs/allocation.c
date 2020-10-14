#include "../includes/asm.h"

t_oper	operation[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 4},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 4},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 4},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 2},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 2},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 2},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 4},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

t_line	*new_line()
{
	t_line	*line;
	int		i;

	line = (t_line *)ft_memalloc(sizeof(t_line));
	line->index = 0;
	line->line_nb = 0;
	line->command = 0;
	line->nb_params = 0;
	line->next = 0;
	line->params_code_byte = 0;
	ft_bzero(line->params_type, 4);
	line->params = (char **)ft_memalloc(sizeof(char *) * 4);
	i = 0;
	while (i < 4)
		line->params[i++] = 0;
	return (line);
}

int		add_line(t_line *line, t_asm *data)
{
	t_line	*tmp;
	t_label	*labels;

	if (!data->lines)
	{
		data->lines = line;
		data->lines->next = NULL;
	}
	else
	{
		tmp = data->lines;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = line;
		tmp->next->next = NULL;
	}
	labels = data->labels;
	while (labels && !labels->dest)
	{
		labels->dest = line;
		labels = labels->next;
	}
}

int		add_label(t_asm *data, char *label)
{
	t_label *new;

	if (!(new = (t_label *)ft_memalloc(sizeof(t_label))))
		return (0);
	new->name = ft_strnew(ft_strlen(label));
	ft_strcpy(new->name, label);
	new->dest = 0;
	new->next = (data->labels) ? data->labels : 0;
	data->labels = new;
	return (1);
}

void	data_initialize(t_asm *data)
{
	data->name = 0;
	data->file_name = 0;
	data->size = 0;
	data->comment = 0;
	data->num_lines = 1;
	data->oper = operation;
	data->lines = NULL;
	data->labels = NULL;
}

char	parameters_encode(char type, int shift)
{
	type = type / 2 + (type > 0);
	return (type << shift);
}
