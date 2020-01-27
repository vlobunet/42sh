/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:27:48 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 17:28:15 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_func(char *str, t_scanf *q)
{
	if (str)
	{
		ft_strdel(&str);
		str = NULL;
	}
	if (q)
	{
		if (q->cmd)
			ft_strdel(&q->cmd);
		free(q);
		q = NULL;
	}
}

t_i		res(char *cmd, int i, char c)
{
	t_i	q;

	q.k = c;
	q.i = 0;
	while (cmd[i] && cmd[i] != c)
		i++;
	q.i = (cmd[i] == c ? i : -1);
	return (q);
}

t_i		checcmd(char *cmd, char c, int i)
{
	t_i	q;

	q.k = c;
	q.i = 0;
	while (cmd[++i] && cmd[i] != c)
		if (c == '\'')
			return (res(cmd, i, c));
		else if (cmd[i] == c)
		{
			q.i = i;
			return (q);
		}
		else if (cmd[i] == '\\')
			i++;
		else if (cmd[i] && (cmd[i] == '"' || cmd[i] == '`' || cmd[i] == '\''))
		{
			q = checcmd(cmd + i + 1, cmd[i], -1);
			i = i + q.i + 1;
			if (!cmd[i] || q.i == -1)
				return (q);
			q.k = c;
		}
	q.i = ((c != 0 && !cmd[i]) ? -1 : i);
	return (q);
}

t_scanf	*new_scanf(int fd, int size_mess)
{
	t_scanf *q;

	q = (t_scanf *)malloc(sizeof(t_scanf));
	q->cmd = NULL;
	q->key = 0;
	g_sel.pos[0] = size_mess;
	g_sel.pos[2] = 0;
	while (q->key != 10 || q->key != 3 || q->key != 4)
	{
		q->key = 0;
		read(fd, &q->key, 8);
		if (q->key == 3 || q->key == 10 || q->key == 4)
			break ;
		q->key == HOME ? go_to_start_str(size_mess) : 0;
		q->key == END ? go_to_end_str(q->cmd) : 0;
		q->key == ESC ? q->cmd = full_deletion(q->cmd, size_mess) : 0;
		q->key == 32 ? q->cmd = print_sumb(q->key, q->cmd, size_mess) : 0;
		((q->key > 32 && q->key <= 127) || q->key == LEFT || q->key == RIGHT) ?
		q->cmd = line_editing(q->cmd, q->key, size_mess, 0) : 0;
	}
	q->key == 3 ? ft_strdel(&q->cmd) : 0;
	g_sel.pos[0] = size_mess;
	return (q);
}

void	if_dquote_cmd(char *str, t_scanf *q, t_i ret, int key)
{
	if (!g_sel.cmd || !*g_sel.cmd)
		return ;
	while (g_sel.cmd && (ret = checcmd(g_sel.cmd, 0, -1)).i < 0 && key != 3)
	{
		str = ft_strjoin(g_sel.cmd, "\n");
		ft_strdel(&g_sel.cmd);
		g_sel.cmd = ft_strdup(str);
		ft_strdel(&str);
		g_sel.pos[2]++;
		ft_putstr_fd("\n[", 1);
		ft_putchar_fd(ret.k, 1);
		ft_putstr_fd("]> ", 1);
		q = new_scanf(0, ft_strlen("[k]> "));
		if (q->cmd)
			str = (ft_strjoin(g_sel.cmd, q->cmd));
		else if (q->key != 10)
			str = NULL;
		ft_strdel(&g_sel.cmd);
		g_sel.cmd = (str ? ft_strdup(str) : NULL);
		key = q->key;
		free_func(str, q);
	}
	((!g_sel.cmd || ret.i < 0) && key != 3) ? print_error_quote() : 0;
	return ;
}
