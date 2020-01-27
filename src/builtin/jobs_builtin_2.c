/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtin_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 15:08:40 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 15:08:42 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

void		print_processes(t_job *j, int fd)
{
	unsigned	i;
	t_cmd		*p;

	p = j->cmds;
	while (p)
	{
		i = 0;
		while (p->av[i])
		{
			ft_putchar_fd(' ', fd);
			ft_putstr_fd(p->av[i], fd);
			ft_putchar_fd(' ', fd);
			i++;
		}
		p = p->next;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int			ft_jobs(char **argv)
{
	t_job	*j;
	char	*status_str;

	if (argv && argv[1])
		ft_export_error("42sh: jobs: wrong number of arguments");
	j = g_jobs;
	while (j)
	{
		if (job_is_completed(j))
		{
			j = j->next;
			continue;
		}
		else
			status_str = (job_is_stopped(j) ? "stopped" : "running");
		ft_putchar_fd('[', STDOUT_FILENO);
		ft_putnbr_fd(j->nbr, STDOUT_FILENO);
		ft_putstr_fd("] ", STDOUT_FILENO);
		if (g_current_job && g_current_job == j)
			ft_putstr_fd(" + ", STDOUT_FILENO);
		ft_putstr_fd(status_str, STDOUT_FILENO);
		print_processes(j, STDOUT_FILENO);
		j = j->next;
	}
	return (0);
}
