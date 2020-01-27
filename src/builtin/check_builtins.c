/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:55:24 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 14:55:28 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"
#include "builtins.h"

const t_bset g_built_tab[BUILT] = {
	{ "echo", &ft_echo },
	{ "cd", &ft_cd},
	{ "type", &ft_type},
	{"set", &ft_set},
	{"unset", &ft_unset},
	{"export", &ft_export},
	{ "exit", &run_exit },
	{ "jobs", &ft_jobs },
	{ "bg", &ft_bg },
	{ "fg", &ft_fg },
	{ "kill", &ft_kill },
	{ "alias", &check_alias },
	{ "unalias", &check_unalias },
	{ "history", &run_history },
	{ "fc", &run_fc },
	{ "test", &ft_test },
	{ "hash", &ft_hash },
	{ NULL, NULL }
};

int		check_builtins(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->av)
	{
		while (g_built_tab[i].command)
		{
			if (ft_strequ(cmd->av[0], g_built_tab[i].command))
			{
				if (i == B_KILL)
				{
					if (!(cmd->av[1] && (cmd->av[1][0] == '%' ||
						(cmd->av[1][0] == '-' && cmd->av[2] &&
							cmd->av[2][0] == '%'))))
						return (-1);
				}
				return (i);
			}
			++i;
		}
	}
	return (-1);
}

int		ft_built_exe(char **args, t_built cmd)
{
	t_pfb			ft_run;

	ft_run = g_built_tab[cmd].function;
	return (ft_run(args));
}
