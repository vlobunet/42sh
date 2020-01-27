/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <vlobunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 16:19:49 by vlobunet          #+#    #+#             */
/*   Updated: 2018/08/16 16:55:41 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	go_to_start_str(int size_mess)
{
	g_sel.pos[2] == 0 ?
	tputs(tgetstr("bl", NULL), 1, printnbr) : 0;
	while (g_sel.pos[1] != 0)
		go_left(1, size_mess);
	while (g_sel.pos[0] != size_mess)
		go_left(1, size_mess);
}

void	go_to_end_str(char *cmd)
{
	int	size;

	size = (int)ft_strlen(cmd);
	g_sel.pos[2] == size ?
	tputs(tgetstr("bl", NULL), 1, printnbr) : 0;
	while (g_sel.pos[2] != size)
		go_right(cmd, 1);
}

void	go_to_next_word(char *cmd)
{
	int	i;

	i = ft_strlen(cmd);
	if (g_sel.pos[2] >= i)
	{
		tputs(tgetstr("bl", NULL), 1, printnbr);
		return ;
	}
	if (cmd[g_sel.pos[2]] != 32)
		while (g_sel.pos[2] < i && cmd[g_sel.pos[2]] != 32)
			go_right(cmd, 1);
	while (g_sel.pos[2] < i && cmd[g_sel.pos[2]] == 32)
		go_right(cmd, 1);
}

void	go_to_prev_word(char *cmd, int size_mess)
{
	if (g_sel.pos[2] == 0)
	{
		tputs(tgetstr("bl", NULL), 1, printnbr);
		return ;
	}
	if (g_sel.pos[2] - 1 > 0 && cmd[g_sel.pos[2]] != 32 &&
		cmd[g_sel.pos[2] - 1] == 32)
		go_left(1, size_mess);
	while (g_sel.pos[2] > 0 && (cmd[g_sel.pos[2]] == 32 ||
		cmd[g_sel.pos[2]] == 0))
		go_left(1, size_mess);
	while (g_sel.pos[2] > 0 && cmd[g_sel.pos[2]] > 32)
		go_left(1, size_mess);
	(g_sel.pos[2] != 0) ? go_right(cmd, 1) : 0;
}

char	*del_previous_word(char *cmd, int size_mess)
{
	char	*dup;
	char	*str;
	char	*tmp;

	dup = ft_strdup(cmd + g_sel.pos[2]);
	go_to_prev_word(cmd, size_mess);
	tmp = del_after_cursor(cmd);
	ft_printf(0, dup, size_mess);
	str = ft_strjoin(tmp, dup);
	ft_strdel(&tmp);
	ft_strdel(&dup);
	return (str);
}
