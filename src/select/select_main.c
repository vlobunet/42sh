/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <vlobunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 11:07:22 by vlobunet          #+#    #+#             */
/*   Updated: 2018/08/16 16:55:25 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	select_right_world(int size_mess, t_select *s)
{
	int	len;

	len = ft_strlen(g_sel.cmd);
	if (g_sel.pos[2] >= len)
		return ;
	if (g_sel.cmd[g_sel.pos[2]] != 32)
		while (g_sel.pos[2] < len && g_sel.cmd[g_sel.pos[2]] != 32)
			select_char(S_R, size_mess, s);
	while (g_sel.pos[2] < len && g_sel.cmd[g_sel.pos[2]] == 32)
		select_char(S_R, size_mess, s);
}

void	select_left_world(int size_mess, t_select *s)
{
	if (g_sel.pos[2] == 0)
	{
		tputs(tgetstr("bl", NULL), 1, printnbr);
		return ;
	}
	if (g_sel.pos[2] - 1 > 0 && g_sel.cmd[g_sel.pos[2]] != 32 &&
		g_sel.cmd[g_sel.pos[2] - 1] == 32)
		select_char(S_L, size_mess, s);
	while (g_sel.pos[2] > 0 && (g_sel.cmd[g_sel.pos[2]] == 32 ||
		g_sel.cmd[g_sel.pos[2]] == 0))
		select_char(S_L, size_mess, s);
	while (g_sel.pos[2] > 0 && g_sel.cmd[g_sel.pos[2]] > 32)
		select_char(S_L, size_mess, s);
	(g_sel.pos[2] != 0) ? select_char(S_R, size_mess, s) : 0;
}

int		select_all_char(int size_mess, t_select *s)
{
	go_to_start_str(size_mess);
	s->os = 0;
	s->s = 0;
	while (g_sel.pos[2] < (int)ft_strlen(g_sel.cmd))
		select_char(S_R, size_mess, s);
	return (0);
}

void	copy_cut_select(int key, t_select *s, int startpos, int size_mess)
{
	char	*cmd;
	char	*lcmd;
	char	*rcmd;

	s->s < 0 ? cmd = ft_strndup(g_sel.cmd + g_sel.pos[2], (s->s * -1)) : 0;
	s->s > 0 ? cmd = ft_strndup(g_sel.cmd + startpos, s->s) : 0;
	g_sel.cpy ? ft_strdel(&g_sel.cpy) : 0;
	g_sel.cpy = ft_strdup(cmd);
	ft_strdel(&cmd);
	if (key == A_CUT)
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
}

void	select_start(long key, int size_mess, t_select *sel)
{
	int	startpos;

	signal(SIGINT, SIG_IGN);
	startpos = g_sel.pos[2];
	while (key == S_L || key == S_R || key == S_H || key == S_E ||
		key == SA_L || key == SA_R || key == A_A)
	{
		if (key == S_H)
			while (g_sel.pos[2] > 0)
				select_char(S_L, size_mess, sel);
		if (key == S_E)
			while (g_sel.pos[2] < (int)ft_strlen(g_sel.cmd))
				select_char(S_R, size_mess, sel);
		(key == SA_R) ? select_right_world(size_mess, sel) : 0;
		(key == SA_L) ? select_left_world(size_mess, sel) : 0;
		(key == A_A) ? startpos = select_all_char(size_mess, sel) : 0;
		(key == S_L || key == S_R) ? select_char(key, size_mess, sel) : 0;
		key = 0;
		read(1, &key, 8);
	}
	tputs(tgetstr("se", NULL), 1, printnbr);
	((key == A_CPY || key == A_CUT) && sel->s != 0) ?
		copy_cut_select(key, sel, startpos, size_mess) : 0;
	check_select_key(key, size_mess, sel, startpos);
	free(sel);
}
