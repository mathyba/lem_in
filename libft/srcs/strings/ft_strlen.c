/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:21:41 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 14:21:17 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

size_t		ft_strlen(char *str)
{
	size_t i;

	i = 0;
	if (!str && ft_printf("str i = %d\n", str[i]))
		return (0);
	while (str[i])
		i++;
	return (i);
}
