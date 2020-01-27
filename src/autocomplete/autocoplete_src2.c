/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocoplete_src2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:35:52 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 15:35:56 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_bin(t_list **lst, char *str, int i, char **fd)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*name;

	fd = ft_strsplit(ft_strchr(run_get_env("PATH", g_sel.m_env, 1), '/'), ':');
	if (str)
		name = (ft_strrchr(str, '/') ?
			ft_strdup(ft_strrchr(str, '/') + 1) : ft_strdup(str));
	else
		name = ft_strdup("");
	while (fd && fd[++i])
	{
		dir = opendir(fd[i]);
		while (dir && (ent = readdir(dir)) != NULL)
			if ((!str || !ft_strncmp(ent->d_name, name, ft_strlen(str))) &&
				ent->d_name[0] != '.')
				ft_lstadd(lst, ft_lstnew(ent->d_name, fd[i]));
		dir ? closedir(dir) : 0;
	}
	while (*lst && (*lst)->prev)
		*lst = (*lst)->prev;
	name ? ft_strdel(&name) : 0;
	ft_freestrarr(fd);
}

char	*set_fd(char *str, char *fd)
{
	char	*home;
	char	*tmp;

	if (str && *str == '/' && !*fd)
	{
		ft_strdel(&fd);
		return (ft_strdup("/"));
	}
	else if (*fd && *fd == '~')
	{
		home = ft_strjoin(ft_get_env_var("HOME="), fd + 1);
		ft_strdel(&fd);
		fd = ft_strdup(home);
		ft_strdel(&home);
		return (fd);
	}
	tmp = ft_strdup(fd);
	ft_strdel(&fd);
	return (tmp);
}

void	get_fd(t_list **lst, char *str)
{
	char			buff[4097];
	char			*fd;
	DIR				*dir;
	struct dirent	*ent;
	char			*name;

	fd = (!str || !ft_strrchr(str, '/') ? ft_strdup(getcwd(buff, 4096)) :
		ft_strndup(str, ft_strlen(str) - ft_strlen(ft_strrchr(str, '/'))));
	fd = set_fd(str, fd);
	dir = opendir(fd);
	if (str)
		name = (ft_strrchr(str, '/') ?
			ft_strdup(ft_strrchr(str, '/') + 1) : ft_strdup(str));
	else
		name = ft_strdup("");
	while ((dir != NULL) && (ent = readdir(dir)) != NULL)
		if ((!str || !ft_strncmp(ent->d_name, name, ft_strlen(name))) &&
			ent->d_name[0] != '.')
			ft_lstadd(lst, ft_lstnew(ent->d_name, fd));
	while (*lst && (*lst)->prev)
		*lst = (*lst)->prev;
	(dir != NULL) ? closedir(dir) : 0;
	fd ? ft_strdel(&fd) : 0;
	name ? ft_strdel(&name) : 0;
}
