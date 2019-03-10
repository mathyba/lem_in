/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isintab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:39:10 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 22:39:13 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isintab(int *tab, int len, int val)
{
	int i;

	i = -1;
	while (++i < len)
		if (tab[i] == val)
			return (1);
	return (0);
}