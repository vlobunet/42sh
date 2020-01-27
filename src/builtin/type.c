/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:24:57 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 19:25:01 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_aliases(t_cmd *cmd)
{
	t_alias *ap;

	ap = g_sel.alias;
	while (ap)
	{
		if (ft_strequ(cmd->av[0], ap->name))
		{
			ft_putstr("an alias for ");
			ft_putendl(ap->value);
			return (1);
		}
		ap = ap->next;
	}
	return (0);
}

static void	check_type(t_cmd *cmd)
{
	if (check_builtins(cmd) >= 0)
	{
		ft_putstr("a shell builtin\n");
		ft_strdel(&cmd->av[0]);
	}
	else if (check_aliases(cmd))
		ft_strdel(&cmd->av[0]);
	else if (ft_find(cmd, MUTE))
	{
		ft_putendl(cmd->path);
		ft_strdel(&cmd->av[0]);
		ft_strdel(&cmd->path);
	}
	else
	{
		ft_putstr("not found\n");
		ft_strdel(&cmd->av[0]);
	}
}

int			ft_type(char **argv)
{
	char	**ptr;
	t_cmd	*cmd;
	int		i;

	if (!argv || !argv[1])
		return (1);
	ptr = argv;
	i = 1;
	cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd));
	cmd->av = (char**)ft_memalloc(sizeof(char*));
	while (ptr[i])
	{
		ft_putstr(ptr[i]);
		ft_putstr(" is ");
		cmd->av[0] = ft_strdup(ptr[i]);
		cmd->av[1] = NULL;
		check_type(cmd);
		++i;
	}
	free(cmd->av);
	free(cmd);
	return (0);
}
