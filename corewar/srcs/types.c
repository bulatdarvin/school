#include "../includes/asm.h"

int		set_types(t_line *line)
{
	int i;

	i = -1;
	t_line *tmp;
	i = 0;
	while (i < line->nb_params)
	{
		if (line->params[i][0] == 'r')
			line->params_type[i] = T_REG;
		else if(line->params[i][0] == '%')
			line->params_type[i] = T_DIR;
		else
			line->params_type[i] = T_IND;
		i++;
	}
}

int		check_types(t_line *line, t_asm *data)
{
	int		i;
	t_oper	oper;

	oper = data->oper[line->command - 1];
	i = 0;
	while (i  < oper.nb_params)
	{
		if (!(oper.argv[i] & line->params_type[i]))
			return (1);
		i++;
	}
	return (0);
}

void	parameters__eval_code_byte(t_line *line)
{
	if (line->command == 1 || line->command == 9
		|| line->command == 12 || line->command == 15)
		return ;
	line->params_code_byte += parameters_encode(line->params_type[0], 6)
							+ parameters_encode(line->params_type[1], 4)
							+ parameters_encode(line->params_type[2], 2);
}


int		line_size(t_line *line, t_oper op)
{
	int		i;
	int		direct_size;
	int		size;

	direct_size = op.direct_size;
	size = 1 + (line->params_code_byte != 0);
	i = -1;
	while (i++ < line->nb_params - 1)
	{
		size += (line->params_type[i] == T_REG)
				+ ((line->params_type[i] == T_DIR) * direct_size)
				+ ((line->params_type[i] == T_IND) * IND_SIZE);
	}
	return (size);
}

int		make_types(t_asm *data)
{
	t_line	*line;
	int		i;

	line = data->lines;
	while (line)
	{
		line->index = data->size;
		set_types(line);
		if (check_types(line, data))
			return (0);
		parameters__eval_code_byte(line);
		data->size += line_size(line, data->oper[line->command - 1]);
		line = line->next;
	}
	return (1);
}
