/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semenbegunov <semenbegunov@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 22:42:55 by semenbegunov      #+#    #+#             */
/*   Updated: 2019/09/11 23:12:52 by semenbegunov     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include "get_next_line.h"

void 	test_static(void)
{
	static char *static_c;

	printf("p=%p\n", static_c);
}


int			file_open(int *fd, char *file_name)
{
	*fd = open(file_name, O_RDWR);
	if (*fd < 0)
	{
		return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	int		fd;
	int		i;
	char 	filename[] = "testfile";
	char 	*line;

	if (file_open(&fd, filename) != 0)
	{
		get_next_line(fd, &line);
		close(fd);
	}
}