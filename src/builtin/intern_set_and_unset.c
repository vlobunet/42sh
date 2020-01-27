/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_set_and_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:08:52 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 19:08:55 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_move_env(int i, int find)
{
	if (find)
	{
		while (g_sel.m_env[i] != NULL)
		{
			if (g_sel.m_env[i] != NULL)
				free(g_sel.m_env[i]);
			if (!g_sel.m_env[i + 1])
				g_sel.m_env[i] = NULL;
			else
				g_sel.m_env[i] = ft_strdup(g_sel.m_env[i + 1]);
			++i;
		}
	}
}

void		ft_unsetenv(char *args)
{
	int		i;
	int		len;
	int		find;

	find = 0;
	if (args)
	{
		len = ft_strlen(args);
		i = 0;
		while (g_sel.m_env[i] != NULL)
		{
			if (ft_strnequ(args, g_sel.m_env[i], len)
				&& (g_sel.m_env[i][len] == '=' || g_sel.m_env[i][len] == '\0'))
			{
				find = 1;
				break ;
			}
			i++;
		}
		ft_move_env(i, find);
	}
}

void		unset_intvar(char *var)
{
	size_t		len;
	t_intvar	*ptr;
	t_intvar	*prev;

	len = ft_strlen(var);
	ptr = g_sel.intvar;
	prev = NULL;
	while (ptr)
	{
		if (ft_strnequ(var, ptr->var, len) && (ptr->var[len] == '\0' ||
			ptr->var[len] == '='))
		{
			if (ptr == g_sel.intvar)
				g_sel.intvar = g_sel.intvar->next;
			else
				prev->next = ptr->next;
			if (ptr->exp == EXPORTED)
				ft_unsetenv(var);
			free(ptr->var);
			free(ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

int			ft_unset(char **argv)
{
	if (!argv[1])
		return (ft_export_error("42sh: unset: not enough arguments"));
	if (ft_strchr(argv[1], '='))
		return (ft_export_error("42sh: unset: invalid parameter name"));
	unset_intvar(argv[1]);
	return (0);
}

int			ft_set(char **argv)
{
	t_intvar *ptr;

	if (argv[1])
		return (ft_export_error("42sh: set: wrong number of arguments"));
	ptr = g_sel.intvar;
	while (ptr)
	{
		ft_putendl(ptr->var);
		ptr = ptr->next;
	}
	return (0);
}
