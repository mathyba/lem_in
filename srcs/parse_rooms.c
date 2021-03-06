/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:40:04 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/17 02:05:26 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Input: room name
** Returns true if name has already been stored | false otherwise
*/

static int		is_dup(ENV *e, char *str, int max_index)
{
	int i;

	i = -1;
	while (++i < max_index)
		if (ft_strequ(str, e->ins->room[i].name))
			return (1);
	return (0);
}

static int		store_room(ENV *e, t_room **tab, t_list *anthill, int *i)
{
	char	**split;

	if (!(split = ft_strsplit((char *)anthill->content, ' ')))
		return (ERR_ALLOC);
	if (!split[0])
	{
		display_warning(e, WRNG_INPUT);
		return (ERR_NOTUBE);
	}
	if (!(e->ins->room[*i].name = (char *)ft_strdup(split[0])))
		return (ERR_ALLOC);
	ft_4vinit(&(*tab)[*i].pos, ft_atoi(split[1]), ft_atoi(split[2]), 0);
	ft_free_strtab(&split);
	link_command(e, ROOM, *i);
	if (is_dup(e, (*tab)[*i].name, *i))
	{
		display_warning(e, WRNG_DUP);
		return (ERR_NOTUBE);
	}
	++*i;
	return (NO_ERR);
}

/*
** stores room names in char **tab, while checking if duplicate room names
** link with commands if command(s) detected and unlinked
*/

static int		store_room_in_tab(ENV *e, t_room **tab, t_list *anthill)
{
	int		i;
	int		ret;

	i = 0;
	while (anthill && ((unsigned int)i < e->graphe->nb_rooms))
	{
		if (((char *)anthill->content)[0] != '#')
		{
			if ((ret = store_room(e, tab, anthill, &i)))
				return (ret);
		}
		else if (((char *)anthill->content)[1] == '#')
			get_command(e, ((char *)anthill->content), 1);
		anthill = anthill->next;
	}
	return (NO_ERR);
}

/*
** allocate rooms and commands,
** scans anthill, returns err code if error, 0 if success
*/

int				store_rooms(ENV *e)
{
	t_list	*tmp;
	int		rooms;
	int		commands;

	tmp = e->anthill;
	rooms = e->graphe->nb_rooms + 1;
	commands = e->ins->nb_commands + 1;
	e->ins->room = (t_room *)ft_memalloc(sizeof(t_room) * (rooms + 1));
	e->ins->commands = (int **)ft_memalloc(sizeof(int *) * (commands + 1));
	if (!e->ins->room || !e->ins->commands)
		return (ERR_ALLOC);
	while (((char *)tmp->content)[0] == '#'
			&& (((char *)tmp->content)[1] != '#'))
		tmp = tmp->next;
	while (ft_atoi(tmp->content) != e->ins->nb_ants)
	{
		display_warning(e, WRNG_FAILED_START);
		tmp = tmp->next;
	}
	tmp = tmp->next;
	return (store_room_in_tab(e, &e->ins->room, tmp));
}

/*
** ### Check room info, store in list, # mark start and end
** Input: line read on stdin, broken up by space
** Returns true if room valid and successfully stored | false otherwise
*/

int				get_room(ENV *e, char **str)
{
	int		ret;

	if (str[1] && str[2] && !str[3])
	{
		if (!ft_isnumber(str[1]) || !ft_isnumber(str[2]))
			display_warning(e, WRNG_COORD);
		else if ((ret = ft_beyond_limiti(str[1])))
			display_warning(e, ret > 0 ? WRNG_INTMAX : WRNG_INTMIN);
		else if ((ret = ft_beyond_limiti(str[2])))
			display_warning(e, ret > 0 ? WRNG_INTMAX : WRNG_INTMIN);
		else if (str[0][0] == 'L')
			display_warning(e, WRNG_ROOM_CHAR);
		else if (++e->graphe->nb_rooms)
			return (NO_ERR);
		e->nb_line *= -1;
		return (ERR_NOTUBE);
	}
	e->nb_line *= -1;
	display_warning(e, WRNG_ROOM);
	return (ERR_NOTUBE);
}
