/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_back_slash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:24:26 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/13 16:24:35 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	free_func(char *str, t_scanf *q)
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

void		if_back_slash(char *str, t_scanf *q)
{
	if (g_sel.cmd && *g_sel.cmd && g_sel.cmd[ft_strlen(g_sel.cmd) - 1] == '\\')
	{
		str = ft_strjoin(g_sel.cmd, "\n");
		ft_strdel(&g_sel.cmd);
		g_sel.cmd = ft_strdup(str);
		ft_strdel(&str);
		g_sel.pos[2]++;
		ft_putstr_fd("\n> ", 1);
		q = new_scanf(0, ft_strlen("> "));
		if (q && q->cmd != NULL)
			str = (ft_strjoin(g_sel.cmd, q->cmd));
		else if (q->key != 10)
			str = NULL;
		ft_strdel(&g_sel.cmd);
		g_sel.cmd = (str ? ft_strdup(str) : NULL);
		free_func(str, q);
		if_back_slash(NULL, NULL);
	}
}
