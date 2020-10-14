#include "ft_printf/includes/struct.h"

/*
# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define REG_NUMBER				16

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define MAGIC_SPACE	4
# define NAME_SPACE		(PROG_NAME_LENGTH + 1 + 4 - (PROG_NAME_LENGTH + 1) % 4)
# define LENGTH_SPACE	4
# define COMMENT_SPACE	(COMMENT_LENGTH + 1 + 4 - (COMMENT_LENGTH + 1) % 4)

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct	s_oper
{
	char			*name;
	int				nb_params;
	int				argv[3];
	int				op_code;
	int				cycles;
	char			*lname;
	int				octal;
	int				direct_size;
}t_oper;

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

typedef struct	s_line
{
	int		index;
	int		line_nb;
	int		command;
	char	**params;
	int		nb_params;
	char	params_type[4];
	char	params_code_byte;
	struct s_line	*next;
}	t_line;

typedef struct s_label
{
	char *name;
	t_line *dest;
	struct s_label *next;
} t_label;

typedef struct s_asm
{
	int num_lines;
	char *name;
	char *file_name;
	int size;
	char *comment;
	t_label *labels;
	t_oper *oper;
	t_line *lines;
} t_asm;

*/
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
/*
int is_comment_or_empty(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == COMMENT_CHAR|| line[i] == 0)
		return (1);
	return (0);
}
*/
/*
int handle_name(char *line, t_asm *data)
{
	int i;
	int start;

	i = 5;

	while (line[i] && line[i] != '"')
		i++;
	if (line[i] != '"')
		return (0);
	start = i + 1;
	i++;
	while (line[i] && line[i] != '"')
		i++;
	if (line[i] != '"' && line[i + 1] != 0)
		return (0);
//	if (i - start == 0)
//		return (0);
	data->name = ft_strsub(line, start, i - start);
	if (ft_strlen(data->name) > PROG_NAME_LENGTH)
		return (0);
	return (1);

	
}

int read_all_comment(t_asm *data, int fd)
{
	char *to_add;
	char *tmp;
	char *position;
	char *buf;

	while (get_next_line(fd, &tmp) > 0)
	{
		if ((position = ft_strchr(tmp, '"')))
		{
			*position = 0;
			data->comment = ft_strjoin(data->comment, tmp);
			//ft_printf("SIZEOF: %d\n", ft_strlen(data->comment));
			return((ft_strlen(data->comment) < COMMENT_LENGTH));
		}
		to_add = ft_strjoin(tmp, "\n");
		buf = data->comment;
		data->comment = ft_strjoin(data->comment, to_add);
		free(to_add);
		data->num_lines++;
		ft_strdel(&tmp);
		ft_strdel(&buf);
	}
}

int handle_comment(char *line, t_asm *data, int fd)
{
	int i;
	int start;

	i = 8;

	while (line[i] && line[i] != '"')
		i++;
	if (line[i] != '"')
		return (0);
	start = i + 1;
	i++;
	while (line[i] && line[i] != '"')
		i++;
	if (line[i])
	{
	//	if (i - start == 0)
	//		return (0);
		data->comment = ft_strsub(line, start, i - start);
	}
	else
	{
		data->comment = ft_strjoin(ft_strdup(line + start), "\n");
		read_all_comment(data, fd);
	}
	//ft_printf("LEN: %d\n", ft_strlen(data->comment));
	return((ft_strlen(data->comment) < COMMENT_LENGTH));
}


int read_name_and_comment(int fd, t_asm *data)
{
	char *line;
	char *tmp;

	data->num_lines = 1;
	while (!(data->name && data->comment) && get_next_line(fd, &line) > 0)
	{
		tmp = line;
		if (is_comment_or_empty(line))
		{
			free(line);
			continue ;
		}
		while (*line == ' ' || *line == '\t')
			line++;
		if (ft_strnequ(line, NAME_CMD_STRING, 5) && !handle_name(line, data))	
		{
			free(line);	
			return (0);
		}
		if (ft_strnequ(line, COMMENT_CMD_STRING, 8) && !handle_comment(line, data, fd))
		{
			free(line);
			return (0);
		}
		free(tmp);
		data->num_lines++;
	}
}
*/
char *cut_line(char *line)
{
	char *dst;
	int i;

	i = 0;
	while (line[i] != COMMENT_CHAR && line[i])
		i++;
	if (line[i] == COMMENT_CHAR)
		line[i] = 0;
	return (line);
}

/*
t_line *new_line()
{
	t_line *line;
	int i;

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
*/
int wrong_symbol(char s)
{
	if (s >= 'a' || s <= 'z')
		return (0);
	if (s >= '0' || s <= '9' || s == '_')
		return (0);
	return (1);
}

/*
int add_label(t_asm *data, char *label)
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
*/
char *handle_label(char *line, t_asm *data)
{
	int i;
	int start;
	char *label;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != LABEL_CHAR && line[i] != ' ' && line[i] != '\t')
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
/*
char *parse_operations(char *line, t_asm *data, t_line *new)
{
	int i;
	int op;
	int start;
	char *operation;

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
*/
/*
int	is_label(char *line)
{
	int i;

	i = 0;
	while (line[i])
		if (ft_strchr(LABEL_CHARS, line[i++]) == 0)
			return (0);
	return (1);
}
*/
/*
int		parser_is_digits(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
*/
/*
char *get_param(char *line, t_line *new, int nb_param)
{
	int start;
	int i;
	char *param;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != SEPARATOR_CHAR && line[i] != ' ' && line[i] != '\t')
		i++;
	if (!(param = ft_strsub(line, start, i - start)))
		return (0);
	if ((param[0] == '%' && parser_is_digits(param + 1)) || (param[0] =='%' && param[1] == ':' 
	&& is_label(param + 2)) || 
	(param[0] == 'r' && ft_atoi(param + 1) > 0 && ft_atoi(param + 1) <= REG_NUMBER) ||
	(param[0] != 'r' && ft_isdigit(param[0])))
	{
		new->params[nb_param] = param;
		return (line + i + 1);
	}
	free(param);
	return (0);
}

char *parse_params(char *line, t_asm *data, t_line *new)
{
	char *tmp;
	int nb_param;
	int start;

	nb_param = 0;
	tmp = line;
	while (nb_param < new->nb_params && *line)
	{
		while (*line && (*line == ' ' || *line == '\t'))
			line++;
		if (!(line = get_param(line, new, nb_param)))
			return(0);
		nb_param++;
	}
	if (nb_param != new->nb_params)
		return (0);
	return (line);
}

int parse_line_instruct(char *line, t_asm *data, t_line *new)
{
	line = parse_operations(line, data, new);
	
	if (line == 0)
		return (0);
	ft_putendl(line);
	line = parse_params(line, data, new);
	if (line == 0)
		return (0);
	new->line_nb = data->num_lines;
}
*/
/*
int	add_line(t_line *line, t_asm *data)
{
	t_line *tmp;
	t_label *labels;

	if (!data->lines)
	{
		//data->lines = (t_line *)ft_memalloc(sizeof(t_line));
		data->lines = line;
		data->lines->next = NULL;
	}
	else
	{
		tmp = data->lines;
		while (tmp->next)
			tmp = tmp->next;
		//tmp->next = (t_line *)ft_memalloc(sizeof(t_line));
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
*/
/*
int handle_operations(char *line, t_asm *data)
{
	char *tmp;
	t_line *new;

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

int parse(int fd, t_asm *data)
{
	char *line;

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

int reader(int fd, t_asm *data)
{
	ft_putendl("ASFSF");
	if (!read_name_and_comment(fd, data))
		return (0);
	if (!parse(fd, data))
		return (0);
	return (1);
}
*/
/*
int set_types(t_line *line)
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

int	check_types(t_line *line, t_asm *data)
{
	int i;
	t_oper oper;

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

char	parameters_encode(char type, int shift)
{
	type = type / 2 + (type > 0);
	return (type << shift);
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


int line_size(t_line *line, t_oper op)
{
	int i;
	int direct_size;
	int size;

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

int	make_types(t_asm *data)
{
	t_line *line;
	int i;

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
*/
/*
int	find_label(t_asm *data, int nb, char *to_find)
{
	t_label *label;

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
	char *s;
	char *tmp;

	s = ft_itoa((target - line->index) % MEM_SIZE);
	if (direct)
	{
		tmp = ft_strjoin("%", s);
		free(s);
		return(tmp);
	}
	return (s);
}

int	labels_replace(t_asm *data)
{
	ft_putendl("ASFSF");
	t_line *line;
	int i;
	int target;
	int direct;

	line = data->lines;
	
	while (line)
	{
		i = -1;
		while (++i < line->nb_params)
		{		
			direct = line->params[i][1] == LABEL_CHAR;
			if (line->params[i][0] == LABEL_CHAR || direct)
			{
				if ((target = find_label(data, line->line_nb, line->params[i] + 1 + direct)) == -1)
					return (0);
				free(line->params[i]);
				line->params[i] = label_to_num(line, direct, target);
			}
		}
		line = line->next;
	}
	return (1);
}
*/
/*
char	*file_create_name(char *path)
{
	int		len;
	char	*name;
	char	*tmp;
	char	*file_name;

	len = (int)(ft_strrchr(path, '.') - path);
	if (!(name = ft_strsub(path, 0, len)))
		return (0);
	tmp = name;
	if (!(file_name = ft_strjoin(name, ".cor")))
	{
		free(name);
		return (0);
	}
	free(tmp);
	return (file_name);
}

void	file_num(int nb, char type, int direct_size, int fd)
{
	int		i;
	char	*buf;

	buf = (char *)&nb;
	if (type == T_REG)
		ft_putchar_fd((char)nb, fd);
	else if (type == T_DIR || type == T_IND)
	{
		i = type == T_DIR ? direct_size : 2;
		while (i--)
			ft_putchar_fd(buf[i], fd);
	}
	else
	{
		i = 4;
		while (i--)
			ft_putchar_fd(buf[i], fd);
	}
}

void	file_write_params(t_asm *data, t_line *line, int fd)
{
	t_oper	op;
	int		nb;
	int		shift;
	int		direct_size;
	int		i;

	op = data->oper[line->command - 1];
	direct_size = op.direct_size;
	i = -1;
	while (++i < line->nb_params)
	{
		shift = line->params[i][0] == 'r' || line->params[i][0] == '%';
		nb = ft_atoi(line->params[i] + shift);
		file_num(nb, line->params_type[i], direct_size, fd);
	}
}

void	file_write_header(t_asm *data, int fd)
{
	int		pad;

	file_num(COREWAR_EXEC_MAGIC, 0, 0, fd);
	ft_putstr_fd(data->name, fd);
	pad = NAME_SPACE - ft_strlen(data->name);
	while (pad > 0)
	{
		ft_putchar_fd(0, fd);
		pad--;
	}
	file_num(data->size, 0, 0, fd);
	ft_putstr_fd(data->comment, fd);
	pad = COMMENT_SPACE - ft_strlen(data->comment);
	while (pad)
	{
		ft_putchar_fd(0, fd);
		pad--;
	}
}

int		file_write(t_asm *data, int fd, char *path)
{

	t_line	*line;

	if (!(data->file_name = file_create_name(path))
	|| (fd = open(data->file_name, O_WRONLY
	| O_CREAT, S_IRWXU | S_IRWXO)) == -1)
	{
		ft_printf("error in file writing\n");
		return (0);
	}
	ft_printf("Writing output program to %s\n", data->file_name);
	file_write_header(data, fd);
	line = data->lines;
	while (line)
	{
		ft_putchar_fd((char)line->command, fd);
		if (line->params_code_byte)
			ft_putchar_fd(line->params_code_byte, fd);
		file_write_params(data, line, fd);
		line = line->next;
	
	}
	close(fd);
	return (1);
}
*/
/*
void	data_initialize(t_asm *data)
{
	data->name = 0;
	data->file_name = 0;
	data->size = 0;
	data->comment = 0;
	data->num_lines = 0;
	data->oper = operation;
	data->lines = NULL;
	data->labels = NULL;
}*/

void	free_all(t_asm *data)
{
	t_line *line;
	t_label *label;

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

int main(char **argv, int argc)
{
	int fd;
	char *line;
	t_asm data;

	data_initialize(&data);
	fd = open("test.s", O_RDONLY);
	if (!reader(fd, &data) || !make_types(&data) || 
		!labels_replace(&data) || !file_write(&data, fd, "test.s"))
		{
			ft_putendl("ERROR in End");
			free_all(&data);
			return (0);
		}
	free_all(&data);
}