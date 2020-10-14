#include "../includes/asm.h"

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
