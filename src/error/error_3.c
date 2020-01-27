/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 13:52:38 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 13:52:45 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		int_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

char	*null_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (NULL);
}
