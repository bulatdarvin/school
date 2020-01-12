#include "includes/struct.h"
#include <stdio.h>

void	ft_putstrc(const char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == 'C')
		{
			ft_putchar(c);
			i += 2;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

int main()
{
  ft_putstrc("\023[35mr$C\023[0m\t", 'b');
  //printf("%.5s\n","1234567");
  return (0);
}
