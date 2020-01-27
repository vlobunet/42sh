/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_do_le_nd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <vlobunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 16:20:33 by vlobunet          #+#    #+#             */
/*   Updated: 2018/08/16 16:56:11 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	go_left_src(int size, int real_pos, int size_mess)
{
	if (g_sel.cmd[g_sel.pos[2] - 1] == '\n')
	{
		real_pos = g_sel.pos[2] - 2;
		while (real_pos > 0 && g_sel.cmd[real_pos] != '\n')
		{
			real_pos--;
			size++;
		}
		while (g_sel.pos[0] != (g_sel.pos[1] > 0 ? size + 1 :
			size_mess + size + 2))
		{
			ft_putchar_fd('\b', 1);
			g_sel.pos[0]--;
		}
	}
}

void	go_left(int flag, int size_mess)
{
	struct winsize	s;

	if (ioctl(0, TIOCGWINSZ, (char *)&s) < 0 ||\
	(g_sel.pos[2] <= 0 && g_sel.pos[0] <= size_mess))
	{
		tputs(tgetstr("bl", NULL), 1, printnbr);
		return ;
	}
	if (g_sel.pos[0] == 0)
	{
		while (g_sel.pos[0] != s.ws_col - 1)
		{
			g_sel.pos[0]++;
			tputs(tgetstr("nd", NULL), 1, printnbr);
		}
		tputs(tgetstr("up", NULL), 1, printnbr);
		g_sel.pos[1]--;
		go_left_src(0, 0, size_mess);
	}
	ft_putchar_fd('\b', 1);
	g_sel.pos[0] = g_sel.pos[0] - 1;
	flag == 1 ? g_sel.pos[2]-- : 0;
}

void	go_right(char *cmd, int flag)
{
	struct winsize	s;

	if (ioctl(0, TIOCGWINSZ, (char *)&s) < 0 ||\
		(g_sel.pos[2] + 1) > (int)ft_strlen(cmd))
	{
		tputs(tgetstr("bl", NULL), 1, printnbr);
		return ;
	}
	if (g_sel.pos[0] + 1 == s.ws_col || g_sel.cmd[g_sel.pos[2]] == '\n')
	{
		while (g_sel.pos[0] != 0)
		{
			g_sel.pos[0]--;
			ft_putchar_fd('\b', 1);
		}
		tputs(tgetstr("do", NULL), 1, printnbr);
		g_sel.pos[1]++;
	}
	g_sel.cmd[g_sel.pos[2]] != '\n' ?
	tputs(tgetstr("nd", NULL), 1, printnbr) : 0;
	g_sel.cmd[g_sel.pos[2]] != '\n' ? g_sel.pos[0]++ : 0;
	flag == 1 ? g_sel.pos[2]++ : 0;
}

char	*go_up(char *cmd, int size_mess)
{
	struct winsize	s;
	int				point;
	char			*tmp;

	if (ioctl(0, TIOCGWINSZ, (char *)&s) < 0)
		return (NULL);
	if (g_sel.pos[1] == 0)
		return (history_up(cmd, size_mess));
	if (g_sel.pos[0] <= size_mess && g_sel.pos[1] == 1)
		go_to_start_str(size_mess);
	else
	{
		point = g_sel.pos[0];
		while (g_sel.pos[0] != 0)
			go_left(1, size_mess);
		go_left(1, size_mess);
		if (point < g_sel.pos[0])
			while (g_sel.pos[0] != point)
				go_left(1, size_mess);
	}
	tmp = ft_strdup(cmd);
	ft_strdel(&cmd);
	return (tmp);
}

char	*go_down(char *cmd, int size_mess)
{
	struct winsize	s;
	int				point;
	int				size;
	char			*tmp;

	size = ft_strlen(cmd);
	if (ioctl(0, TIOCGWINSZ, (char *)&s) < 0)
		return (NULL);
	if (g_sel.pos[2] == size)
		return (history_down(cmd, size_mess));
	point = g_sel.pos[0];
	go_right(cmd, 1);
	while (g_sel.pos[0] != point && g_sel.pos[2] != size)
		go_right(cmd, 1);
	tmp = ft_strdup(cmd);
	ft_strdel(&cmd);
	return (tmp);
}
