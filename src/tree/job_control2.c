/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:29:17 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 15:29:20 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "sh.h"

static void	set_retcode(int ret)
{
	char *tmp;
	char *retcode;

	if (g_sel.shell_interactive)
	{
		retcode = ft_itoa(ret);
		tmp = ft_strjoin("?=", retcode);
		set_intvar(tmp, INTERN, NULL, 0);
		free(tmp);
		free(retcode);
	}
}

static void	set_status(t_cmd *p, pid_t pid, int status)
{
	int ret;

	p->status = status;
	if (WIFSTOPPED(status))
	{
		ft_putstr_fd("\n[+] suspended ", STDOUT_FILENO);
		ft_putnbr_fd((int)pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		p->state |= STOPPED;
		ret = 128 + WSTOPSIG(p->status);
	}
	else
	{
		p->state |= COMPLETED;
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			sync();
			ft_putnbr_fd((int)pid, STDERR_FILENO);
			ft_putstr_fd(": Process terminated\n", STDERR_FILENO);
			ret = 128 + WTERMSIG(p->status);
		}
	}
	set_retcode(ret);
}

static int	check_process(t_job **j, t_cmd *p, pid_t pid, int status)
{
	while (p)
	{
		if (p->pid == pid)
		{
			set_status(p, pid, status);
			return (NORM);
		}
		p = p->next;
	}
	*j = (*j)->next;
	return (ERROR);
}

int			check_status(pid_t pid, int status)
{
	t_job	*j;
	t_cmd	*p;

	if (pid > 0)
	{
		j = g_jobs;
		while (j)
		{
			p = j->cmds;
			if (check_process(&j, p, pid, status) == NORM)
				return (0);
		}
		return (-1);
	}
	else if (pid == 0 || errno == ECHILD)
		return (-1);
	else
		return (-1);
}
