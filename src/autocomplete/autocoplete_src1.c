/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocoplete_src1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:34:52 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 15:35:01 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		pr_autoc(t_token *t, char *lstr, char *word, int size_mess)
{
	char	*tmp;
	char	*swap;
	int		i;
	char	*name;

	if (t->type == 1)
		name = ft_strdup("");
	else
		name = (ft_strrchr(t->content, '/') ?
		ft_strdup(ft_strrchr(t->content, '/') + 1) : ft_strdup(t->content));
	tmp = (name ? ft_strjoin(word + ft_strlen(name), lstr) : ft_strdup(word));
	i = ft_strlen(word + ft_strlen(name));
	g_sel.cmd = del_after_cursor(g_sel.cmd);
	ft_printf(0, tmp, size_mess);
	swap = ft_strjoin(g_sel.cmd, tmp);
	ft_strdel(&g_sel.cmd);
	g_sel.cmd = ft_strdup(swap);
	ft_strdel(&lstr);
	swap ? ft_strdel(&swap) : 0;
	tmp ? ft_strdel(&tmp) : 0;
	name ? ft_strdel(&name) : 0;
	return (i);
}

void	go_right_name(int i)
{
	while (i > 0)
	{
		go_right(g_sel.cmd, 1);
		i--;
	}
}

void	check_key(long key, int size_mess, int flag)
{
	key == HOME ? go_to_start_str(size_mess) : 0;
	key == END ? go_to_end_str(g_sel.cmd) : 0;
	key == ESC ? g_sel.cmd = full_deletion(g_sel.cmd, size_mess) : 0;
	key == DEL ? g_sel.cmd = del_after_cursor(g_sel.cmd) : 0;
	key == ALT_RT ? go_to_next_word(g_sel.cmd) : 0;
	key == ALT_LT && g_sel.pos[0] > 0 ?
		go_to_prev_word(g_sel.cmd, size_mess) : 0;
	key == 23 && g_sel.pos[2] > 0 ?
		g_sel.cmd = del_previous_word(g_sel.cmd, size_mess) : 0;
	((key >= 32 && key <= 127) || key == LEFT || key == RIGHT || key == UP ||
	key == DOWN) ? g_sel.cmd = line_editing(g_sel.cmd, key, size_mess, 0) : 0;
	key == '\n' && flag ? go_right_name(flag) : 0;
}

void	free_all(t_tmp tmp, t_token *t)
{
	ft_strdel(&tmp.left);
	ft_strdel(&tmp.right);
	ft_lstdel_all(&tmp.e);
	ft_tokdel_all(&t);
}
