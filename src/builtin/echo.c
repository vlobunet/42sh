/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:40:19 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 15:40:21 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_echo(char **argv)
{
	int	i;
	int	opt;

	opt = 0;
	i = 1;
	while (argv[i])
	{
		if (ft_strequ(argv[i], "-n"))
		{
			opt = 1;
			++i;
			continue;
		}
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		++i;
	}
	if (!opt)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
