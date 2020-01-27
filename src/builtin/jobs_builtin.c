/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:11:52 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 19:11:54 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

static void	set_job_as_running(t_job *j)
{
	t_cmd	*p;

	p = j->cmds;
	while (p)
	{
		p->state &= ~STOPPED;
		p = p->next;
	}
	j->notified = 0;
}

int			continue_job(t_job *j, int foreground)
{
	set_job_as_running(j);
	if (foreground)
		run_foreground(j, 1);
	else
		run_background(j, 1);
	return (0);
}

int			ft_bg(char **args)
{
	t_job		*j;
	unsigned	nbr;

	if (!args[1] && g_current_job)
		return (continue_job(g_current_job, 0));
	if (args[1] && args[1][0] == '%')
	{
		nbr = ft_atoi(&args[1][1]);
		j = g_jobs;
		while (j)
		{
			if (nbr == j->nbr)
				break ;
			j = j->next;
		}
		if (j)
			continue_job(j, 0);
		else
			return (ft_export_error("42sh: kill: no such job"));
	}
	return (0);
}

int			ft_fg(char **args)
{
	t_job		*j;
	unsigned	nbr;

	if (!args[1] && g_current_job)
		return (continue_job(g_current_job, 1));
	if (args[1] && args[1][0] == '%')
	{
		nbr = ft_atoi(&args[1][1]);
		j = g_jobs;
		while (j)
		{
			if (nbr == j->nbr)
				break ;
			j = j->next;
		}
		if (j)
			continue_job(j, 1);
		else
			return (ft_export_error("42sh: kill: no such job"));
	}
	return (0);
}

int			ft_kill(char **args)
{
	t_job		*j;
	unsigned	nbr;

	if (args[1] && args[1][0] == '%')
	{
		nbr = ft_atoi(&args[1][1]);
		j = g_jobs;
		while (j)
		{
			if (nbr == j->nbr)
				break ;
			j = j->next;
		}
		if (j)
			kill(-j->pgid, SIGKILL);
		else
		{
			ft_putstr_fd("42sh: kill: no such job\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}
