/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:48:15 by odrinkwa          #+#    #+#             */
/*   Updated: 2019/11/29 20:45:34 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "lemin_mlx.h"
#include "mlx.h"
#include "fdf.h"
#include "float.h"
#include <stdio.h>

void			set_start_conditions(t_lemin_mlx *lm)
{
	if (lm->lem->count_rooms > 100)
	{
		lm->show_room_numbers = 0;
		lm->show_interm_rooms = 0;
	}
	if (lm->lem->count_all_edges_moving > 1000000)
	{
		lm->show_ways = 0;
	}
}

void			initialize(t_lemin_mlx *lm, t_lemin *l, t_mlx *m)
{
	lemin_init(l);
	tmlx_initialize(m, 1400, 1000);
	tlemin_mlx_initialize(lm);
	errno = 0;
}

void			set_lemin(t_lemin *lemin)
{
	check_data(lemin);
	set_numbers_rooms(lemin);
	check_data(lemin);
	prepare_data(lemin);
	set_num_rooms_to_ant_moves(lemin);
}

int				main(int argc, char **argv)
{
	t_lemin		lemin;
	t_mlx		m;
	t_lemin_mlx	lm;

	initialize(&lm, &lemin, &m);
	open_file_load_data(&lemin, argc, argv);
	set_lemin(&lemin);
	load_anthill_to_map_points(&m, &lemin);
	calc_parameter_maps(&m);
	make_map_points(&m);
	correct_color(&m);
	lm.m = &m;
	lm.lem = &lemin;
	create_ant_draw_move(&lm);
	if (tmlx_create_mlx(&m, "lemin") == 0)
		finish_all(&lm, -1);
	start_load_ant_im(&lm);
	set_start_conditions(&lm);
	lemin_keyhook(-1, (void*)&lm);
	mlx_key_hook(m.win, lemin_keyhook, (void*)&lm);
	mlx_loop_hook(m.ptr, loop_ants_move, (void*)&lm);
	mlx_loop(m.ptr);
	finish_prog(&lemin, 0, -1, NULL);
}
