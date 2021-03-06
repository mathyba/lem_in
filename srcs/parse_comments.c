/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:01:15 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/17 01:50:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Set start to index value
*/

void			c_start(ENV *e, int index)
{
	if (e->ins->commands[index] && e->ins->commands[index][1] != ROOM)
		display_warning(e, WRNG_FAILED_START);
	if (e->graphe->start != -1)
		display_warning(e, WRNG_DOUBLE_START);
	e->graphe->start = e->ins->commands[index][2];
}

/*
** Set end to index value
*/

void			c_end(ENV *e, int index)
{
	if (e->ins->commands[index][1] != ROOM)
		display_warning(e, WRNG_FAILED_END);
	if (e->graphe->end != -1)
		display_warning(e, WRNG_DOUBLE_END);
	e->graphe->end = e->ins->commands[index][2];
}

/*
** ### Check comment format, marks start and end for following room reading
** Input: line read on stdin, not broken up
** Prints comment and returns true if comment OK | false otherwise
*/

int				apply_commands(ENV *e)
{
	static void		(*f[NB_COMMANDS])(ENV *e, int index) = {&c_start, &c_end};
	int				index;

	index = -1;
	if (!e->graphe->map)
		return (ERR_NOTUBE);
	while (++index < e->ins->nb_commands)
	{
		if (e->ins->commands[index])
			f[e->ins->commands[index][0]](e, index);
	}
	if (e->graphe->start == -1)
		return (ERR_START);
	if (e->graphe->end == -1)
		return (ERR_END);
	if (e->graphe->start == e->graphe->end)
		return (NO_ERR);
	return (NO_ERR);
}

/*
** Upon reaching next significant line, store info on element targeted by
** undealt command
** static linked keeps cursor on first undealt command in command list,
** all following ones ** being also undealt
** Input: type = type of item targeted by command (room or tube),
** and their index in corresponding storage
*/

void			link_command(ENV *e, int type, int index)
{
	static int	linked;

	while (e->ins->commands[linked] && linked < e->ins->nb_commands)
	{
		e->ins->commands[linked][1] = type;
		e->ins->commands[linked][2] = index;
		++linked;
	}
}

/*
** Checks if comment or command, adds latter to command list
** Returns TRUE or FALSE if comment or command, to later skip significant input
** treatment
** if command, store in int **tab : in 0 index in ref table,
** type of target room or tube, index in corresponding storage
*/

int				get_command(ENV *e, char *str, int option)
{
	static int	index;
	static char	ref[NB_COMMANDS][8] = {COMMAND_START, COMMAND_END};
	int			i;

	if (!str || str[1] != '#')
		return (0);
	i = 0;
	while (i < NB_COMMANDS)
	{
		if (ft_strequ(str, ref[i]))
		{
			if (option == 0 && ++e->ins->nb_commands)
				return (1);
			break ;
		}
		++i;
	}
	if (i == NB_COMMANDS)
		return (0);
	e->ins->commands[index] = (int *)ft_memalloc(sizeof(int) * 3);
	e->ins->commands[index][0] = i;
	if (index < NB_COMMANDS)
		++index;
	return (i);
}
