/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:36:34 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 14:36:36 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

static void	set_shlvl(void)
{
	int		shlvl;
	char	*nbr;
	char	buf[PATH_MAX];
	char	*tmp;

	nbr = get_copy_env("SHLVL", MUTE);
	shlvl = (nbr ? ft_atoi(nbr) + 1 : 1);
	nbr = ft_itoa(shlvl);
	tmp = ft_strjoin("SHLVL=", nbr);
	set_intvar(tmp, EXPORTED, NULL, 0);
	free(nbr);
	free(tmp);
	tmp = ft_strjoin("PWD=", getcwd(buf, PATH_MAX));
	set_intvar(tmp, EXPORTED, NULL, 0);
	free(tmp);
	set_intvar("0=42sh", INTERN, NULL, 0);
	nbr = ft_itoa(getpid());
	tmp = ft_strjoin("$=", nbr);
	set_intvar(tmp, INTERN, NULL, 0);
	free(nbr);
	free(tmp);
}

void		copy_env(void)
{
	extern char		**environ;
	int				size;
	char			**copy;
	int				i;

	i = 0;
	g_sel.intvar = NULL;
	size = env_size(environ);
	copy = (char**)ft_memalloc(sizeof(char*) * (size + 1));
	if (!copy)
	{
		ft_putstr_fd("42sh: Out of memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (environ[i])
	{
		copy[i] = ft_strdup(environ[i]);
		push_intvar(environ[i], EXPORTED);
		++i;
	}
	copy[i] = NULL;
	g_sel.m_env = copy;
	set_shlvl();
}
