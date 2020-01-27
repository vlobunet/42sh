/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmessage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:38:09 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 14:38:11 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_goto(char *cwd, char *homedir)
{
	char	*pwd;
	char	*home;
	size_t	len;

	if (homedir)
	{
		len = ft_strlen(homedir);
		if (ft_strnequ(homedir, cwd, len))
		{
			home = "~";
			cwd += len;
		}
		else
			home = "";
	}
	else
		home = "";
	pwd = ft_strjoin(home, cwd);
	return (pwd);
}

void	ft_print_message(void)
{
	char	buff[4097];
	char	*pwd;

	sync();
	g_sel.savetty = get_default_settings();
	g_sel.strlen_mes = 0;
	g_sel.cmd = NULL;
	get_cursor_x() != 1 ? ft_putchar_fd('\n', 1) : 0;
	if (!getintvar(g_sel.intvar, "?") ||
		!ft_strcmp(ft_strchr(getintvar(g_sel.intvar, "?"), '=') + 1, "0"))
		ft_putstr_fd("\033[01;38;05;46m➜ \033[01;38;05;51m", 1);
	else
		ft_putstr_fd("\033[01;38;05;196m➜ \033[01;38;05;51m", 1);
	pwd = ft_goto(getcwd(buff, 4096), get_copy_env("HOME", MUTE));
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd(" $> ", 1);
	ft_putstr_fd("\033[0m", 1);
	g_sel.strlen_mes = ft_strlen(pwd) + 6;
	ft_strdel(&pwd);
	g_sel.pos[0] = g_sel.strlen_mes;
	g_sel.pos[1] = 0;
}
