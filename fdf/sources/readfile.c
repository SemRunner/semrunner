/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:41:58 by odrinkwa          #+#    #+#             */
/*   Updated: 2019/10/18 17:11:33 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static char		*nextnum(char *str)
{
	while ((*str == '-' || ft_isdigit(*str)) && *str != '\0')
		str++;
	while (*str != '-' && !(ft_isdigit(*str)) && *str != '\0')
		str++;
	return (str);
}

static int		check_fdf_line(char *line)
{
	int		count_nums;
	char	*pos;

	pos = line;
	while (*line != '\0')
	{
		if (!((ft_isdigit(*line) || *line == ' ' || *line == '-')))
			return (-1);
		line++;
	}
	line = pos;
	if (*line == ' ')
		count_nums = -1;
	else
		count_nums = 0;
	while (*line != '\0')
	{
		line = nextnum(line);
		count_nums++;
	}
	if (count_nums < 0)
		return (-1);
	return (count_nums);
}

int				check_file(t_mlx *m, int fd)
{
	char	*line;
	int		tmp_check_line;
	int		res;

	line = NULL;
	while ((res = get_next_line(fd, &line)) == 1)
	{
		if ((tmp_check_line = check_fdf_line(line)) < 0)
			return (-1);
		else
			m->map_x = m->map_x > (tmp_check_line) ? m->map_x : tmp_check_line;
		m->map_y++;
		ft_memdel((void **)&line);
	}
	if (line != NULL)
		ft_memdel((void**)&line);
	if (res == -1)
		return (-1);
	return (1);
}

int				put_map(t_mlx *m, int fd)
{
	char	*line;
	char	*pos;
	int		res;
	int		i;
	int		j;

	i = 0;
	line = NULL;
	while ((res = get_next_line(fd, &line)) == 1)
	{
		pos = line;
		j = -1;
		while (++j < m->map_x && *pos != '\0')
		{
			m->map[i * m->map_x + j] = ft_atoi(pos);
			pos = nextnum(pos);
		}
		ft_memdel((void**)&line);
		i++;
	}
	if (line != NULL)
		ft_memdel((void**)&line);
	if (res == -1)
		return (-1);
	return (1);
}
