/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:17:16 by ssilvana          #+#    #+#             */
/*   Updated: 2020/10/15 13:17:17 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_asm	data;

	if (argc == 2)
	{
		data_initialize(&data);
		argc = 0;
		fd = open(argv[1], O_RDONLY);
		if (!reader(fd, &data) || !make_types(&data) ||
			!labels_replace(&data) || !file_write(&data, fd, argv[1]))
		{
			ft_putendl("ERROR");
			free_all(&data);
			return (0);
		}
		free_all(&data);
		return (0);
	}
	ft_putendl("No File");
}
