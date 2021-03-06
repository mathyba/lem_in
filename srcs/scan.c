/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 06:07:55 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 19:35:33 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** loops through moves and display result
** one move comprises:
** - checking if next room is empty
** - moving all ants in anthill to the next room,
** - introducing new ants in anthill (if enough ants and free rooms)
*/

int		scan_allmoves(ENV *e, int display)
{
	int	nb_comb;
	int	high_comb;
	int arrived;

	nb_comb = 0;
	e->turns = 0;
	if (!(arrived = 0) && !e->all_paths)
		return (ERR_SOLUTION);
	while (e->all_paths[nb_comb])
		++nb_comb;
	high_comb = nb_comb;
	if (!(e->ants = (int **)ft_memalloc(sizeof(int *) * (e->ins->nb_ants + 1))))
		return (ERR_ALLOC);
	ft_printf("%s", display ? "\n" : "");
	while (arrived < e->ins->nb_ants)
	{
		++nb_comb;
		move_next_room(e);
		ant_enter_path(e, high_comb);
		arrived = display_travelling(e, display);
	}
	ft_free_inttab(&e->ants, e->ins->nb_ants);
	return (NO_ERR);
}
