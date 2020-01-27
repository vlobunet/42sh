/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:32:24 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 12:32:27 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"

int		count_size_hash(char **array)
{
	int		i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != NULL)
	{
		i++;
	}
	if (i > 2)
	{
		ft_putstr("42sh: Use hash or  hash [-d]\n");
		return (0);
	}
	return (1);
}

void	print_incor_flag(char *flag)
{
	ft_putstr("42sh: Incorect flag - [ ");
	ft_putstr(flag);
	ft_putstr(" ]\n");
}
