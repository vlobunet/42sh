/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:36:52 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 14:36:55 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

static int	ft_env_rewrite(char *str, int size)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = (char**)ft_memalloc(sizeof(char*) * (size + 2));
	if (!new_envp)
	{
		ft_putstr_fd("42sh: Out of memory\n", STDERR_FILENO);
		run_exit(NULL);
	}
	while (i < size)
	{
		new_envp[i] = ft_strdup(g_sel.m_env[i]);
		i++;
	}
	new_envp[size] = ft_strdup(str);
	if (new_envp[size] == NULL)
	{
		ft_putstr_fd("42sh: Cannot set env\n", STDERR_FILENO);
		run_exit(NULL);
	}
	new_envp[size + 1] = NULL;
	ft_freestrarr(g_sel.m_env);
	g_sel.m_env = new_envp;
	return (0);
}

int			env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		++i;
	return (i);
}

int			ft_setenv(char *var)
{
	int		size;
	int		i;
	size_t	len;

	size = env_size(g_sel.m_env);
	len = 0;
	i = 0;
	while (var[len] && var[len] != '=')
		++len;
	while (i < size)
	{
		if (ft_strnequ(var, g_sel.m_env[i], len) && (g_sel.m_env[i][len] == '='
			|| g_sel.m_env[i][len] == '\0'))
		{
			if (ft_strequ(g_sel.m_env[i], var))
				return (0);
			free(g_sel.m_env[i]);
			g_sel.m_env[i] = ft_strdup(var);
			return (0);
		}
		++i;
	}
	ft_env_rewrite(var, size);
	return (0);
}
