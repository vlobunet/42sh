/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:28:31 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 19:28:33 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		print_error_term(void)
{
	ft_putstr_fd("ERROR: The device is not a terminal!\n", 2);
	exit(EXIT_FAILURE);
}

void		print_error_data(int i)
{
	if (i == -1)
		ft_putstr_fd("ERROR: Description of the \
			current terminal was not found!\n", 2);
	else if (i == 0)
		ft_putstr_fd("ERROR: Description of the current terminal empty!\n", 2);
	exit(EXIT_FAILURE);
}

void		print_error_quote(void)
{
	ft_putendl_fd("\n42sh: unexpected EOF while looking for matching `\"'", 2);
}

int			ft_err_message(char *s)
{
	if (s)
	{
		ft_putstr_fd("42sh: syntax error  ", 2);
		ft_putstr_fd(s, 2);
	}
	else
		ft_putstr_fd("42sh: parse error ", 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

t_history	**error_get(void)
{
	ft_putendl_fd("fc: events can't be executed backwards, aborted", 2);
	return (NULL);
}
