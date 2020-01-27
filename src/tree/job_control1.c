/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:28:47 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 15:28:50 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

static void	notify_jobs(t_job **j, t_job **jlast, t_job **jnext)
{
	while (*j)
	{
		*jnext = (*j)->next;
		if (job_is_completed(*j))
		{
			if (*jlast)
				(*jlast)->next = *jnext;
			else
				g_jobs = *jnext;
			free_job(*j);
			*j = NULL;
		}
		else if (job_is_stopped(*j) && !(*j)->notified)
		{
			(*j)->notified = 1;
			*jlast = *j;
		}
		else
			*jlast = *j;
		*j = *jnext;
	}
}

void		update_jobs(void)
{
	t_job		*j;
	t_job		*jlast;
	t_job		*jnext;

	update_status();
	jlast = NULL;
	j = g_jobs;
	notify_jobs(&j, &jlast, &jnext);
}

void		run_foreground(t_job *j, int cont)
{
	tcsetpgrp(g_sel.shell_terminal, j->pgid);
	if (!job_is_completed(j))
		g_current_job = j;
	if (cont)
	{
		tcsetattr(g_sel.shell_terminal, TCSAFLUSH, &j->tmodes);
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_putendl_fd("42sh: kill(SIGCONT) error", STDERR_FILENO);
	}
	wait_for_job(j);
	tcsetpgrp(g_sel.shell_terminal, g_sel.shell_pgid);
	tcgetattr(g_sel.shell_terminal, &j->tmodes);
	tcsetattr(g_sel.shell_terminal, TCSAFLUSH, &g_sel.savetty);
}

void		run_background(t_job *j, int cont)
{
	if (cont)
	{
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_putendl_fd("42sh: continue error", STDERR_FILENO);
	}
}

void		job_control(t_job *job)
{
	if (!g_sel.shell_interactive)
		wait_for_job(job);
	else if (!job->bg)
		run_foreground(job, 0);
	else
		run_background(job, 0);
}
