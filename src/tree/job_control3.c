/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:40:14 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 15:40:16 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "sh.h"

void			wait_for_job(t_job *j)
{
	int			status;
	pid_t		pid;
	t_cmd		*last;
	t_cmd		*tmp;

	last = j->cmds;
	status = 0;
	while (last->next)
		last = last->next;
	pid = waitpid(last->pid, &status, WUNTRACED);
	check_status(pid, status);
	tmp = j->cmds;
	while (tmp != last)
	{
		pid = waitpid(tmp->pid, &status, WUNTRACED | WNOHANG);
		if (pid == 0)
			tmp->state |= COMPLETED;
		check_status(pid, status);
		tmp = tmp->next;
	}
	return ;
}

void			update_status(void)
{
	int			status;
	pid_t		pid;
	int			res;

	status = 0;
	res = 0;
	while (res == 0)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
		res = check_status(pid, status);
	}
}

int				job_is_stopped(t_job *j)
{
	t_cmd		*p;

	p = j->cmds;
	while (p)
	{
		if (!(p->state & (STOPPED)))
			return (0);
		p = p->next;
	}
	return (1);
}

int				job_is_completed(t_job *j)
{
	t_cmd		*p;

	p = j->cmds;
	while (p)
	{
		if (!(p->state & COMPLETED))
			return (0);
		p = p->next;
	}
	return (1);
}

void			free_job(t_job *j)
{
	int			cur;
	sigset_t	set;

	cur = 0;
	sigfillset(&set);
	sigprocmask(SIG_SETMASK, &set, NULL);
	ft_freecmdlist(j->cmds);
	if (g_current_job == j)
		cur = 1;
	free(j);
	j = NULL;
	if (cur)
		g_current_job = g_jobs;
	sigemptyset(&set);
	sigprocmask(SIG_SETMASK, &set, NULL);
}
