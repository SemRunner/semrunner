/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_all_anthill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:25:04 by odrinkwa          #+#    #+#             */
/*   Updated: 2019/11/24 23:09:05 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin_mlx.h"
#include "mlx.h"
#include "fdf.h"

static void		lemin_legend1(t_lemin_mlx *lm)
{
	char	str[50];
	t_mlx	*m;

	m = lm->m;
	str[0] = '\0';
	ft_printf("%ynumber of ants: %d", str, lm->lem->number_of_ants);
	mlx_string_put(m->ptr, m->win, 10, 690, 0x9f9e90,
		str);
	str[0] = '\0';
	ft_printf("%ynumber of steps: %d", str, lm->lem->max_step);
	mlx_string_put(m->ptr, m->win, 10, 710, 0x9f9e90, str);
	str[0] = '\0';
	ft_printf("%ycurrent step: %d", str, lm->lem->current_step);
	mlx_string_put(m->ptr, m->win, 10, 730, 0x9f9e90, str);
}

void			lemin_legend(t_lemin_mlx *lm, int color)
{
	char	str[50];
	t_mlx	*m;

	m = lm->m;
	str[0] = '\0';
	mlx_string_put(m->ptr, m->win, 10, 480, 0xFFFFFF, "ANTHILL KEYS:");
	mlx_string_put(m->ptr, m->win, 10, 500, color,
					"steps                 : <, >");
	mlx_string_put(m->ptr, m->win, 10, 520, color, "reset steps to 0      : /");
	if (lm->nonstop == 0)
		mlx_string_put(m->ptr, m->win, 10, 540, color, "nonstop (off)     : m");
	else
		mlx_string_put(m->ptr, m->win, 10, 540, color, "nonstop (on)      : m");
	mlx_string_put(m->ptr, m->win, 10, 560, color, "change size rooms : ', \\");
	str[0] = '\0';
	ft_printf("%ychange speed ants(%2d): [, ]", str, lm->speed);
	mlx_string_put(m->ptr, m->win, 10, 580, color, str);
	mlx_string_put(m->ptr, m->win, 10, 600, color,
					"show/remove room names : p");
	mlx_string_put(m->ptr, m->win, 10, 620, color,
					"show/remove not used edges : o");
	mlx_string_put(m->ptr, m->win, 10, 640, color,
					"type of edges ant moves : n");
	mlx_string_put(m->ptr, m->win, 10, 670, 0xFFFFFF, "ANTHILL INFO:");
	lemin_legend1(lm);
}

void			put_names_rooms(t_mlx *m, t_lemin *l, t_lemin_mlx *lm,
									int color)
{
	int			i;
	t_point		point_draw_room;

	if (lm->show_room_numbers == 0)
		return ;
	i = -1;
	while (++i < l->count_rooms)
	{
		if (lm->lem->rooms[i]->flow != 1 && lm->show_not_use_edges != 1)
			continue ;
		point_draw_room = get_point_to_draw(m, i);
		mlx_string_put(m->ptr, m->win,
			point_draw_room.x + (lm->size_ant_im) / 2 + 5,
			point_draw_room.y,
			color,
			((l->rooms)[i])->name);
	}
}

void			put_main_image(t_lemin_mlx *lm)
{
	mlx_put_image_to_window(((t_mlx*)((t_lemin_mlx*)lm)->m)->ptr,
						((t_mlx*)((t_lemin_mlx*)lm)->m)->win,
						((t_mlx*)((t_lemin_mlx*)lm)->m)->main_im, 0, 0);
}

void			put_all_anthill(void *lm)
{
	put_main_image(lm);
	main_legend(((t_lemin_mlx*)lm)->m);
	put_names_rooms(((t_lemin_mlx*)lm)->m, ((t_lemin_mlx*)lm)->lem,
					((t_lemin_mlx*)lm), 0xFF0000);
	lemin_legend(((t_lemin_mlx*)lm), 0xFFFF00);
}
