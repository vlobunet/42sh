/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:53:33 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 19:53:35 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*get_env(char *env, char **env_g)
{
	int		i;
	char	*env_join;
	int		size;

	i = -1;
	env_join = ft_strjoin(env, "=");
	size = ft_strlen(env_join);
	while (env_g[++i])
		if (ft_strncmp(env_g[i], env_join, size) == 0)
		{
			ft_strdel(&env_join);
			return (env_g[i] + size);
		}
	ft_putstr_fd("getenv: Wrong atribut: ", 2);
	ft_putendl_fd(env, 1);
	ft_strdel(&env_join);
	return (NULL);
}

char	*run_get_env(char *env, char **env_g, int flag)
{
	int		i;
	char	*env_join;
	int		size;

	i = -1;
	env_join = ft_strjoin(env, "=");
	size = ft_strlen(env_join);
	while (env_g && env_g[++i])
		if (ft_strncmp(env_g[i], env_join, size) == 0)
		{
			ft_strdel(&env_join);
			return (env_g[i]);
		}
	flag ? ft_putstr_fd("Oops! ", 2) : 0;
	flag ? ft_putstr_fd(env, 2) : 0;
	flag ? ft_putendl_fd(": Not found!", 2) : 0;
	ft_strdel(&env_join);
	return (NULL);
}
