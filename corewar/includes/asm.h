#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "../ft_printf/includes/struct.h"
# define MAGIC_SPACE	4
# define NAME_SPACE		(PROG_NAME_LENGTH + 1 + 4 - (PROG_NAME_LENGTH + 1) % 4)
# define LENGTH_SPACE	4
# define COMMENT_SPACE	(COMMENT_LENGTH + 1 + 4 - (COMMENT_LENGTH + 1) % 4)


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
/*
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
*/

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

int		handle_name(char *line, t_asm *data);
int		read_all_comment(t_asm *data, int fd);
int		handle_comment(char *line, t_asm *data, int fd);
int		read_name_and_comment(int fd, t_asm *data);

t_line	*new_line();
int		add_line(t_line *line, t_asm *data);
int 	add_label(t_asm *data, char *label);
void 	data_initialize(t_asm *data);
char	parameters_encode(char type, int shift);

int 	is_comment_or_empty(char *line);
char 	*cut_line(char *line);
int 	wrong_symbol(char s);
int		parser_is_digits(char *str);
int		is_label(char *line);

int		parse(int fd, t_asm *data);
int		reader(int fd, t_asm *data);
int		handle_operations(char *line, t_asm *data);

char 	*parse_operations(char *line, t_asm *data, t_line *new);
char 	*get_param(char *line, t_line *new, int nb_param);
char 	*parse_params(char *line, t_asm *data, t_line *new);
int		parse_line_instruct(char *line, t_asm *data, t_line *new);

char	*handle_label(char *line, t_asm *data);
int		find_label(t_asm *data, int nb, char *to_find);
char	*label_to_num(t_line *line, int direct, int target);
int		labels_replace(t_asm *data);

char	*file_create_name(char *path);
void	file_num(int nb, char type, int direct_size, int fd);
void	file_write_params(t_asm *data, t_line *line, int fd);
void	file_write_header(t_asm *data, int fd);
int		file_write(t_asm *data, int fd, char *path);

void	free_all(t_asm *data);
void	lines_free(t_line *lines);

int		set_types(t_line *line);
int		check_types(t_line *line, t_asm *data);
void	parameters__eval_code_byte(t_line *line);
int		line_size(t_line *line, t_oper op);
int		make_types(t_asm *data);

#endif