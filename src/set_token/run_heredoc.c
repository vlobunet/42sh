/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:32:58 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/07 14:32:59 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*run_heredoc(char *str)
{
	int		fd;
	t_scanf	*q;

	g_sel.savetty = get_default_settings();
	fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	while (42 && !g_sel.f)
	{
		ft_putstr_fd("myheredoc> ", 1);
		q = new_scanf(0, ft_strlen("myheredoc> "));
		(q->cmd && ft_strcmp(q->cmd, str)) ? ft_putendl_fd(q->cmd, fd) : 0;
		(!q->cmd && q->key == 10) ? ft_putendl_fd("\n", fd) : 0;
		if ((!q->cmd && (q->key == 4 || q->key == 3)) ||
			(q->cmd && !ft_strcmp(q->cmd, str)))
			break ;
		ft_putchar_fd('\n', 1);
		q ? ft_strdel(&q->cmd) : 0;
		q ? free(q) : 0;
	}
	res_default_settings(g_sel.savetty);
	fd ? close(fd) : 0;
	fd = q->key;
	q ? ft_strdel(&q->cmd) : 0;
	q ? free(q) : 0;
	return (fd == 3 ? "/dev/null" : "/tmp/.heredoc");
}
