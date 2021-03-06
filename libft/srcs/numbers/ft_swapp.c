/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:25:23 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 18:26:03 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** swap pointers
*/

void		ft_swapp(void **a, void **b)
{
	char *c;
	char **aa;
	char **bb;

	aa = (char **)a;
	bb = (char **)b;
	c = *aa;
	*aa = *bb;
	*bb = c;
}
