/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:49:38 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 14:49:40 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	add_aliases(t_alias **list, char *name, char *value)
{
	t_alias *al;

	if (!name || !value || !*name || !*value)
		return ;
	al = (t_alias *)malloc(sizeof(t_alias));
	al->name = ft_strdup(name);
	al->value = ft_strdup(value);
	al->prev = NULL;
	al->next = NULL;
	if (list && *list)
	{
		(*list)->next = al;
		al->prev = *list;
	}
	*list = al;
}

void	creat_alias(t_alias **list)
{
	add_aliases(list, "l", "ls -lahG");
	add_aliases(list, "la", "ls -lAhG");
	add_aliases(list, "ll", "ls -lhG");
	add_aliases(list, "ls", "ls -G");
	add_aliases(list, "md", "mkdir -pG");
	while (*list && (*list)->prev)
		*list = (*list)->prev;
	g_sel.alias = *list;
}

void	print_all_alias(void)
{
	t_alias *alias;

	alias = g_sel.alias;
	if (!alias)
		ft_putendl_fd("aliases empty", 1);
	while (alias)
	{
		ft_putstr_fd(alias->name, 1);
		ft_putstr_fd("=\'", 1);
		ft_putstr_fd(alias->value, 1);
		ft_putendl_fd("\'", 1);
		alias = alias->next;
	}
}

int		create_new_alias(char **cmd, t_alias *alias)
{
	alias = g_sel.alias;
	if (!alias)
	{
		add_aliases(&g_sel.alias, *cmd, *(cmd + 2));
		ft_putendl_fd("alias created!", 1);
		return (1);
	}
	while (alias)
	{
		if (!ft_strcmp(alias->name, *cmd))
		{
			ft_strdel(&alias->value);
			alias->value = ft_strdup(*(cmd + 2));
			ft_putendl_fd("alias updated!", 1);
			return (1);
		}
		else if (!alias->next)
		{
			add_aliases(&alias, *cmd, *(cmd + 2));
			ft_putendl_fd("alias created!", 1);
			return (1);
		}
		alias = alias->next;
	}
	return (1);
}

int		check_alias(char **cmd)
{
	int ret;

	ret = 0;
	cmd = cmd + 1;
	if (!cmd || !*cmd)
		print_all_alias();
	else if (*cmd && (ft_isalpha(**cmd) || ft_isdigit(**cmd)) && *(cmd + 1) &&
		!ft_strcmp(*(cmd + 1), "=") && *(cmd + 2) && !*(cmd + 3))
		ret = create_new_alias(cmd, NULL);
	else
		ft_putendl_fd("ERROR: alias is not correct", 1);
	return (ret);
}
