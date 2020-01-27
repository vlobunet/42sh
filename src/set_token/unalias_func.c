/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:05:18 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/02 18:09:57 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		for_print(char *cmd)
{
	ft_putstr_fd("unalias: no such hash table element: ", 1);
	ft_putendl_fd(cmd, 1);
}

void			del_alias(t_alias *tmp)
{
	ft_strdel(&(tmp->name));
	ft_strdel(&(tmp->value));
	if (!tmp->next && !tmp->prev)
	{
		free(g_sel.alias);
		g_sel.alias = NULL;
	}
	else
		free(tmp);
}

int				unalias(char *cmd, t_alias *alias)
{
	t_alias		*tmp;

	alias = g_sel.alias;
	while (alias)
	{
		if (!ft_strcmp(alias->name, cmd))
		{
			tmp = alias;
			if (alias->prev)
			{
				alias->prev->next = alias->next;
				alias->next ? alias->next->prev = alias->prev : 0;
			}
			else
			{
				alias->next ? alias->next->prev = NULL : 0;
				alias->next ? g_sel.alias = alias->next : 0;
			}
			del_alias(tmp);
			return (1);
		}
		alias = alias->next;
	}
	for_print(cmd);
	return (0);
}

int				check_unalias(char **cmd)
{
	int		ret;

	ret = 0;
	if (cmd && *cmd && !*(cmd + 1))
		ret = unalias(*cmd, NULL);
	else
		ft_putendl_fd("unalias: usage: unalias [name ...]", 1);
	return (ret);
}
