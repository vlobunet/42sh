/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:58:32 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/07 14:58:38 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_get_env_var(char *str)
{
	int	i;
	int	size;

	i = 0;
	if (!g_sel.m_env)
		return (NULL);
	size = ft_strlen(str);
	while (g_sel.m_env[i])
	{
		if (ft_strncmp(str, g_sel.m_env[i], size) == 0)
			return (g_sel.m_env[i] + size);
		i++;
	}
	return (NULL);
}

int		change_dir(char *path, char *cwd, char *tmp)
{
	char	buff[4097];

	cwd = getcwd(buff, 4096);
	if (!chdir(path))
	{
		tmp = ft_strjoin("OLDPWD=", cwd);
		set_intvar(tmp, EXPORTED, NULL, 0);
		free(tmp);
		tmp = ft_strjoin("PWD=", getcwd(buff, 4096));
		set_intvar(tmp, EXPORTED, NULL, 0);
		free(tmp);
		return (0);
	}
	ft_putstr_fd("42sh: cd: ", 2);
	if (access(path, F_OK) == -1)
		ft_putstr_fd("no such file or directory: ", 2);
	else if (access(path, R_OK) == -1)
		ft_putstr_fd("permission denied: ", 2);
	else
		ft_putstr_fd("not a directory: ", 2);
	ft_putendl_fd(path, 2);
	return (1);
}

int		ft_cd(char **argv)
{
	char	**argvp;
	char	*tmp;
	int		ret;

	ret = 1;
	argvp = argv + 1;
	if (!argvp || !*argvp || !**argv)
		return (change_dir(get_copy_env("HOME", MUTE), NULL, NULL));
	if (argvp[0] && !argvp[1])
	{
		tmp = ft_strjoin(get_copy_env("HOME", MUTE), argvp[0] + 1);
		if (ft_strequ(argvp[0], "--"))
			ret = (change_dir(get_copy_env("HOME", MUTE), NULL, NULL));
		else if (ft_strequ(argvp[0], "-"))
			ret = (change_dir(ft_get_env_var("OLDPWD="), NULL, NULL));
		else if (ft_strequ(argvp[0], "~"))
			ret = (change_dir(get_copy_env("HOME", MUTE), NULL, NULL));
		else if (argvp[0][0] == '~')
			ret = change_dir(tmp, NULL, NULL);
		else
			ret = (change_dir(argvp[0], NULL, NULL));
		tmp ? ft_strdel(&tmp) : 0;
	}
	return (ret);
}
