/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 17:35:02 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 17:35:04 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

int		make_pipe(t_cmd *cmd, int *fds)
{
	if (cmd->next)
	{
		if (pipe(fds))
		{
			ft_putendl_fd("42sh: pipe() error", STDERR_FILENO);
			return (-1);
		}
		cmd->out_fd = fds[1];
		cmd->next->in_fd = fds[0];
	}
	return (0);
}

int		init_job(t_tree *node, t_job **job, t_cmd *ptr, int bg)
{
	if (!(*job = (t_job*)ft_memalloc(sizeof(t_job))))
	{
		ft_putendl_fd("42sh: out of memory", STDERR_FILENO);
		return (0);
	}
	set_job_number(*job);
	(*job)->cmds = ptr;
	node->command = NULL;
	(*job)->bg = bg;
	if (g_sel.shell_interactive)
	{
		if ((tcgetattr(STDOUT_FILENO, &(*job)->tmodes)) == -1)
			(*job)->tmodes = g_sel.savetty;
	}
	job_push_back(*job);
	return (1);
}
