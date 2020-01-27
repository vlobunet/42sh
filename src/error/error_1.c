/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:28:18 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 19:28:20 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_error(char *error)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(error, 2);
}

void	error_arg(char arg)
{
	ft_putstr_fd("cat: illegal option -- ", 2);
	ft_putchar_fd(arg, 2);
	ft_putstr_fd("\nusage: ft_ls [-eEnb] [file ...]\n", 2);
}

int		error_unset(char *str)
{
	if (str)
	{
		ft_putstr_fd("unsetenv : ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" : wrong attribute!", 2);
	}
	else
		ft_putendl_fd("setenv : invalid number of attributes.", 2);
	return (1);
}

void	print_error_name_t(void)
{
	ft_putstr_fd("ERROR: The name of the terminal was not found!\n", 2);
	exit(EXIT_FAILURE);
}

int		print_error_history(char *str)
{
	ft_putstr_fd("history : ", 2);
	ft_putstr_fd("illegal option ", 2);
	ft_putendl_fd(str, 2);
	ft_putendl_fd("usage: history [-c]", 2);
	return (0);
}
