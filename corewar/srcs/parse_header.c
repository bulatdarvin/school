#include "../includes/asm.h"

int		handle_name(char *line, t_asm *data)
{
	int	i;
	int	start;

	i = 5;
	ft_putendl("AQRQWR");
	while (line[i] && line[i] != '"')
		i++;
	if (line[i] != '"')
		return (0);
	start = i + 1;
	i++;
	while (line[i] && line[i] != '"')
		i++;
	if (line[i] != '"' /*&& line[i + 1] != 0*/)
		return (0);
	data->name = ft_strsub(line, start, i - start);
	if (ft_strlen(data->name) > PROG_NAME_LENGTH)
		return (0);
	return (1);
}

int		read_all_comment(t_asm *data, int fd)
{
	char	*to_add;
	char	*tmp;
	char	*position;
	char	*buf;

	while (get_next_line(fd, &tmp) > 0)
	{
		if ((position = ft_strchr(tmp, '"')))
		{
			*position = 0;
			data->comment = ft_strjoin(data->comment, tmp);
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

int		handle_comment(char *line, t_asm *data, int fd)
{
	int	i;
	int	start;

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
		data->comment = ft_strsub(line, start, i - start);
	else
	{
		data->comment = ft_strjoin(ft_strdup(line + start), "\n");
		read_all_comment(data, fd);
	}
	return((ft_strlen(data->comment) < COMMENT_LENGTH));
}

int error_line(char *line)
{
	free(line);
	return (0);
}

int		read_name_and_comment(int fd, t_asm *data)
{
	char	*line;
	char	*tmp;

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
			return (error_line(line));
		if (ft_strnequ(line, COMMENT_CMD_STRING, 8) && !handle_comment(line, data, fd))
			return (error_line(line));
		free(tmp);
		data->num_lines++;
	}
}
