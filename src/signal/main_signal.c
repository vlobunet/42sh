/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <vlobunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 08:51:17 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/01 17:38:35 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		sigwinch_handler(int signum)
{
	sigset_t set;

	sigfillset(&set);
	sigprocmask(SIG_SETMASK, &set, NULL);
	if (signum == SIGWINCH)
	{
		tputs(tgetstr("cl", NULL), 1, printnbr);
		ft_strdel(&g_sel.cmd);
		g_sel.pos[2] = 0;
		g_sel.pos[1] = 0;
		g_sel.pos[0] = 0;
		ft_print_message();
	}
	sigemptyset(&set);
	sigprocmask(SIG_SETMASK, &set, NULL);
	return ;
}

void		set_child_signals(t_job *job, pid_t pid, struct sigaction act,
	sigset_t set)
{
	if (g_sel.shell_interactive)
	{
		pid = getpid();
		if (!job->pgid)
			job->pgid = pid;
		setpgid(pid, job->pgid);
		if (!job->bg)
		{
			tcsetpgrp(g_sel.shell_terminal, job->pgid);
			sigfillset(&set);
			sigprocmask(SIG_SETMASK, &set, NULL);
			sigfillset(&act.sa_mask);
			act.sa_handler = SIG_DFL;
			sigaction(SIGINT, &act, NULL);
			sigaction(SIGQUIT, &act, NULL);
			sigaction(SIGTSTP, &act, NULL);
			sigaction(SIGTERM, &act, NULL);
			sigaction(SIGTTIN, &act, NULL);
			sigaction(SIGTTOU, &act, NULL);
			sigemptyset(&set);
			sigprocmask(SIG_SETMASK, &set, NULL);
		}
	}
}
