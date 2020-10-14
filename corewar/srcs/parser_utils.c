#include "../includes/asm.h"

int		is_comment_or_empty(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == COMMENT_CHAR|| line[i] == 0)
		return (1);
	return (0);
}

char	*cut_line(char *line)
{
	char	*dst;
	int		i;

	i = 0;
	while (line[i] != COMMENT_CHAR && line[i])
		i++;
	if (line[i] == COMMENT_CHAR)
		line[i] = 0;
	return (line);
}

int		wrong_symbol(char s)
{
	if (s >= 'a' || s <= 'z')
		return (0);
	if (s >= '0' || s <= '9' || s == '_')
		return (0);
	return (1);
}

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

int		is_label(char *line)
{
	int i;

	i = 0;
	while (line[i])
		if (ft_strchr(LABEL_CHARS, line[i++]) == 0)
			return (0);
	return (1);
}
