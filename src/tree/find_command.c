/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:03:26 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 15:03:28 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_access(t_cmd *cmd, char *tmp, char **p_arr, int warning)
{
	if (access(tmp, X_OK) != NORM)
	{
		if (warning == NORM)
		{
			ft_putstr_fd("42sh: ", STDERR_FILENO);
			ft_putstr_fd(tmp, STDERR_FILENO);
			ft_putstr_fd(": permission denied\n", STDERR_FILENO);
			set_intvar("?=126", INTERN, NULL, 0);
		}
		ft_freestrarr(p_arr);
		free(tmp);
		return (0);
	}
	cmd->path = ft_strdup(tmp);
	ft_freestrarr(p_arr);
	free(tmp);
	return (1);
}

static int	ft_path_fitting(t_cmd *cmd, char **p_arr, int warning)
{
	char	*tmp;
	char	*tmp1;
	int		i;

	i = 0;
	while (p_arr[i] != NULL)
	{
		tmp1 = ft_strjoin(p_arr[i], "/");
		tmp = ft_strjoin(tmp1, cmd->av[0]);
		free(tmp1);
		if (access(tmp, F_OK) == NORM)
			return (check_access(cmd, tmp, p_arr, warning));
		if (tmp)
			free(tmp);
		++i;
	}
	if (warning == NORM)
	{
		ft_putstr_fd("42sh: ", STDERR_FILENO);
		ft_putstr_fd(cmd->av[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		set_intvar("?=127", INTERN, NULL, 0);
	}
	ft_freestrarr(p_arr);
	return (0);
}

static void	print_warning(int warning, char *str)
{
	if (warning == NORM)
	{
		ft_putstr_fd("42sh: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": permission denied\n", STDERR_FILENO);
	}
}

int			ft_find(t_cmd *command, int warning)
{
	char	**path_arr;
	char	*env_path;

	if (!command->av[0])
		return (0);
	if (access(command->av[0], F_OK) != NORM)
	{
		if (!(env_path = get_copy_env("PATH", NORM)))
			return (0);
		path_arr = ft_strsplit(env_path, ':');
		if (!path_arr)
			return (0);
		return (ft_path_fitting(command, path_arr, warning));
	}
	else if (access(command->av[0], X_OK) != NORM)
	{
		print_warning(warning, command->av[0]);
		set_intvar("?=126", INTERN, NULL, 0);
		return (0);
	}
	else if (command->av[0][0] == '/')
		command->path = ft_strdup(command->av[0]);
	else
		command->path = ft_strjoin("./", command->av[0]);
	return (1);
}

int			check_commands(t_cmd *commands)
{
	t_cmd	*ptr;
	int		ret;

	ptr = commands;
	ret = 1;
	while (ptr)
	{
		if (ptr->av)
		{
			if ((ret = check_builtins(ptr)) >= 0)
			{
				ptr = ptr->next;
				continue;
			}
			else if (!ft_find(ptr, NORM))
				return (-1);
		}
		ptr = ptr->next;
	}
	return (0);
}
