/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:52:38 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 19:52:42 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	if_attr(char *s, int i)
{
	while (s[++i])
		if (s[i] != 'n')
			return (0);
	return (1);
}

int	run_echo(char **s, int flag, int i)
{
	if (!s || !*s)
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	while (s && s[i] && s[i][0] == '-' && if_attr(s[i], 0))
	{
		flag = 1;
		i++;
	}
	while (s && s[i])
	{
		ft_putstr_fd(s[i++], 1);
		s[i] ? ft_putstr_fd(" ", 1) : 0;
	}
	flag ? ft_putstr_fd("\033[7m%\033[0m", 2) : 0;
	return (1);
}
