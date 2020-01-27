/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_group.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:37:12 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 14:37:15 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

int		run_exit(char **argv)
{
	res_default_settings(g_sel.savetty);
	if (argv)
		ft_freestrarr(argv);
	exit(0);
	return (0);
}

void	init_pos(void)
{
	g_sel.pos[1] = 0;
	g_sel.pos[2] = 0;
	g_sel.pos[0] = 0;
}

void	chld_handler(int signum)
{
	sigset_t set;

	sigfillset(&set);
	sigprocmask(SIG_SETMASK, &set, NULL);
	if (signum == SIGCHLD)
		update_status();
	sigemptyset(&set);
	sigprocmask(SIG_SETMASK, &set, NULL);
	return ;
}

void	set_signals(void)
{
	sigset_t			set;
	struct sigaction	act;

	sigfillset(&set);
	sigprocmask(SIG_SETMASK, &set, NULL);
	ft_memset(&act, 0, sizeof(act));
	sigfillset(&act.sa_mask);
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGTSTP, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
	sigaction(SIGTTIN, &act, NULL);
	sigaction(SIGTTOU, &act, NULL);
	act.sa_handler = chld_handler;
	sigaction(SIGCHLD, &act, NULL);
	act.sa_handler = sigwinch_handler;
	sigaction(SIGWINCH, &act, NULL);
	sigemptyset(&set);
	sigprocmask(SIG_SETMASK, &set, NULL);
	return ;
}

void	init_process_group(void)
{
	g_sel.shell_terminal = STDIN_FILENO;
	g_sel.shell_interactive = isatty(g_sel.shell_terminal);
	if (g_sel.shell_interactive)
	{
		while (tcgetpgrp(g_sel.shell_terminal) !=
			(g_sel.shell_pgid = getpgid(0)))
		{
			ft_putstr_fd("42sh: shell is not interactive\n", STDERR_FILENO);
			kill(-g_sel.shell_pgid, SIGKILL);
		}
		set_signals();
		g_sel.shell_pgid = getpid();
		if (setpgid(g_sel.shell_pgid, g_sel.shell_pgid) < 0)
		{
			ft_putstr_fd("42sh: Can not put the shell in it's own group", 2);
			exit(EXIT_FAILURE);
		}
		tcsetpgrp(g_sel.shell_terminal, g_sel.shell_pgid);
	}
}
