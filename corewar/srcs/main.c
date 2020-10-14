#include "../includes/asm.h"

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
