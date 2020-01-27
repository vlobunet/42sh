/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 16:13:03 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 16:13:05 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

static void	set_io(t_cmd *cmd)
{
	if (cmd->next || cmd->prev || cmd->cmd_type == SUBSHELL)
	{
		if (cmd->prev)
		{
			dup2(cmd->in_fd, STDIN_FILENO);
			close(cmd->in_fd);
		}
		if (cmd->next)
		{
			dup2(cmd->out_fd, STDOUT_FILENO);
			close(cmd->out_fd);
			close(cmd->next->in_fd);
		}
	}
}

static int	handle_subshell(t_cmd *cmd)
{
	char *pid_str;
	char *pid;

	pid = ft_itoa(getpid());
	pid_str = ft_strjoin("$=", pid);
	set_intvar(pid_str, INTERN, NULL, 0);
	ft_strdel(&pid);
	ft_strdel(&pid_str);
	g_sel.shell_interactive = 0;
	g_sel.shell_pgid = 0;
	run_tree(cmd->subtree, 0, 0);
	destruction_tree(cmd->subtree);
	return (ft_atoi(get_intvar("?", NULL)));
}

void		exec_child(t_cmd *cmd, t_job *job, int builtin)
{
	struct sigaction	act;
	sigset_t			set;

	ft_memset(&set, 0, sizeof(set));
	ft_memset(&act, 0, sizeof(act));
	set_io(cmd);
	if (cmd->cmd_type != SUBSHELL)
		set_child_signals(job, act, set);
	if (cmd->redir)
		handle_redirections(cmd->redir);
	if (builtin >= 0)
		exit(ft_built_exe(cmd->av, builtin));
	if (cmd->cmd_type == SUBSHELL)
		exit(handle_subshell(cmd));
	if (execve(cmd->path, cmd->av, g_sel.m_env) < 0)
		ft_putstr_fd("42sh: execve error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
