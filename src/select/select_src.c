/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_src.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <vlobunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 11:07:38 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/01 17:37:32 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_select_key(char key, int flag)
{
	struct winsize	s;

	if (ioctl(0, TIOCGWINSZ, (char *)&s) < 0 || key == 0)
		return ;
	if (g_sel.pos[0] + 1 == s.ws_col)
	{
		while (g_sel.pos[0] != 0)
		{
			g_sel.pos[0]--;
			tputs(tgetstr("le", NULL), 1, printnbr);
		}
		tputs(tgetstr("do", NULL), 1, printnbr);
		g_sel.pos[1] = g_sel.pos[1] + 1;
	}
	ft_putchar_fd(key, 1);
	g_sel.pos[0]++;
	flag == 1 ? g_sel.pos[2]++ : 0;
}

void	select_char(long key, int size_mess, t_select *sel)
{
	if ((key == S_R && g_sel.pos[2] < (int)ft_strlen(g_sel.cmd)) ||
		(key == S_L && g_sel.pos[2] > 0))
	{
		sel->s = (key == S_L ? sel->s - 1 : sel->s + 1);
		(sel->os == 0 && sel->s != 0) ?
			tputs(tgetstr("so", NULL), 1, printnbr) : 0;
		((sel->os > 0 && sel->s > sel->os) ||
			(sel->os < 0 && sel->s < sel->os)) ?
			tputs(tgetstr("so", NULL), 1, printnbr) : 0;
		((sel->os > 0 && sel->s < sel->os) ||
			(sel->os < 0 && sel->s > sel->os)) ?
			tputs(tgetstr("se", NULL), 1, printnbr) : 0;
		key == S_L ? go_left(1, size_mess) : 0;
		print_select_key(g_sel.cmd[g_sel.pos[2]], 1);
		key == S_L ? go_left(1, size_mess) : 0;
		sel->os = sel->s;
	}
	else
		tputs(tgetstr("bl", NULL), 1, printnbr);
}

void	clean_up_select(t_select *s, int startpos, int size_mess)
{
	char	*rcmd;
	char	*cmd;
	int		i;

	i = 0;
	if (s->s < 0)
		ft_printf(0, g_sel.cmd + g_sel.pos[2], size_mess);
	else if (s->s > 0)
	{
		cmd = ft_strndup(g_sel.cmd + startpos, s->s);
		rcmd = ft_strdup(g_sel.cmd + g_sel.pos[2]);
		while (g_sel.pos[2] != startpos)
			go_left(1, size_mess);
		while (cmd[i])
			print_key(cmd[i++], 1);
		i = 0;
		while (rcmd[i])
			print_key(rcmd[i++], 1);
		while (i--)
			go_left(1, size_mess);
		ft_strdel(&rcmd);
		ft_strdel(&cmd);
	}
	s->s = 0;
}

void	paste_select(int size_mess, char *lcmd, char *rcmd, char *tmp)
{
	int		i;

	if (!g_sel.cpy)
		return ;
	i = 0;
	lcmd = (g_sel.cmd ? ft_strndup(g_sel.cmd, g_sel.pos[2]) : NULL);
	rcmd = (g_sel.cmd ? ft_strdup(g_sel.cmd + g_sel.pos[2]) : NULL);
	ft_strdel(&g_sel.cmd);
	tmp = (lcmd ? ft_strjoin(lcmd, g_sel.cpy) : ft_strdup(g_sel.cpy));
	g_sel.cmd = (rcmd ? ft_strjoin(tmp, rcmd) : ft_strdup(tmp));
	while (g_sel.cpy[i])
		print_key(g_sel.cpy[i++], 1);
	i = 0;
	while (rcmd && rcmd[i])
		print_key(rcmd[i++], 1);
	while (i--)
		go_left(1, size_mess);
	ft_strdel(&tmp);
	ft_strdel(&lcmd);
	ft_strdel(&rcmd);
}

void	check_select_key(long key, int size_mess, t_select *s, int startpos)
{
	char	*lcmd;
	char	*rcmd;

	if (key == BACK && s->s != 0)
	{
		s->s > 0 ? rcmd = ft_strdup(g_sel.cmd + g_sel.pos[2]) : 0;
		s->s < 0 ? rcmd = ft_strdup(g_sel.cmd + startpos) : 0;
		if (s->s > 0)
			while (g_sel.pos[2] != startpos)
				go_left(1, size_mess);
		lcmd = del_after_cursor(g_sel.cmd);
		ft_printf(0, rcmd, size_mess);
		g_sel.cmd = ft_strjoin(lcmd, rcmd);
		ft_strdel(&lcmd);
		ft_strdel(&rcmd);
		s->s = 0;
	}
	if (s->s != 0)
		clean_up_select(s, startpos, size_mess);
	key == A_PST && g_sel.cpy ? paste_select(size_mess, NULL, NULL, NULL) : 0;
}
