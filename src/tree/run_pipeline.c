/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 16:30:46 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 16:30:47 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

static void	exec_builtin(t_cmd *ptr, int builtin)
{
	char *retstr;
	char *tmp;

	ptr->state |= COMPLETED;
	if (ptr->redir)
		handle_redirections(ptr->redir);
	tmp = ft_itoa(ft_built_exe(ptr->av, builtin));
	retstr = ft_strjoin("?=", tmp);
	free(tmp);
	set_intvar(retstr, INTERN, NULL, 0);
	free(retstr);
	retstr = NULL;
}

static int	exec_program(t_job *job, t_cmd *ptr, int builtin)
{
	pid_t	pid;

	set_hash_tab(ptr->path, g_hash_tab);
	if ((pid = fork()))
	{
		if (pid < 0)
		{
			ft_putendl_fd("42sh: fork error", STDERR_FILENO);
			return (0);
		}
		ptr->pid = pid;
		if (g_sel.shell_interactive)
		{
			if (!job->pgid)
				job->pgid = pid;
			setpgid(pid, job->pgid);
		}
	}
	else
		exec_child(ptr, job, builtin);
	if (ptr->cmd_type == SUBSHELL)
		destruction_tree(ptr->subtree);
	return (1);
}

static int	exec_command(t_job *job, t_cmd *ptr)
{
	int builtin;

	if (((builtin = check_builtins(ptr)) >= 0)
			&& !ptr->prev && !ptr->next)
		exec_builtin(ptr, builtin);
	else if (!exec_program(job, ptr, builtin))
		return (0);
	ptr->next ? close(ptr->out_fd) : 0;
	ptr->prev ? close(ptr->in_fd) : 0;
	return (1);
}

static void	manage_jobs(t_job *job, int noreset)
{
	if (g_sel.shell_interactive && noreset == 0)
		reset_fd();
	job_control(job);
	update_jobs();
}

int			run_pipeline(t_tree *node, int bg, int noreset)
{
	int		fds[2];
	t_job	*job;
	t_cmd	*ptr;

	if (!node)
		return (0);
	ptr = node->command;
	if (check_commands(ptr) == -1 || !init_job(node, &job, ptr, bg))
		return (0);
	if (node->token == CMD || node->token == GRP)
	{
		while (ptr)
		{
			make_pipe(ptr, fds);
			if (!exec_command(job, ptr))
				return (0);
			ptr = ptr->next;
		}
		manage_jobs(job, noreset);
		if ((!bg && !ft_atoi(get_intvar("?", NULL))) || bg)
			return (1);
	}
	return (0);
}
