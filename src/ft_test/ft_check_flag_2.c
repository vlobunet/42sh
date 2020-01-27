/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flag_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:49:33 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 20:49:35 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

int		ft_check_flag_5(char *args, char *val, char *val2)
{
	struct stat	st;
	struct stat	st2;

	if (ft_strncmp(args, "-z", ft_strlen(args)) == 0)
		return ((ft_strlen(val) == 0) ? 1 : 0);
	if (ft_strncmp(args, "-L", ft_strlen(args)) == 0)
		return ((lstat(val, &st) == 0 && (S_ISLNK(st.st_mode))) ? 1 : 0);
	if (ft_strncmp(args, "-S", ft_strlen(args)) == 0)
		return ((stat(val, &st) == 0 && (S_ISSOCK(st.st_mode))) ? 1 : 0);
	if (ft_strncmp(args, "-nt", ft_strlen(args)) == 0)
	{
		return ((stat(val, &st) == 0 && stat(val2, &st2) == 0
			&& &st.st_ctime > &st2.st_ctime) ? 1 : 0);
	}
	return (-1);
}

int		ft_check_flag_6(char *args, char *val, char *val2)
{
	struct stat	st1;
	struct stat	st2;

	if (ft_strncmp(args, "-ot", ft_strlen(args)) == 0)
	{
		return ((stat(val, &st1) == 0 && stat(val2, &st2) == 0
			&& &st1.st_ctime < &st2.st_ctime) ? 1 : 0);
	}
	if (ft_strncmp(args, "-ef", ft_strlen(args)) == 0)
	{
		return ((stat(val, &st1) == 0 && stat(val2, &st2) == 0
			&& &st1.st_ino == &st2.st_ino) ? 1 : 0);
	}
	if (ft_strncmp(args, "=", ft_strlen(args)) == 0)
		return ((ft_strcmp(val, val2) == 0) ? 1 : 0);
	if (ft_strncmp(args, "!=", ft_strlen(args)) == 0)
		return ((ft_strcmp(val, val2) != 0) ? 1 : 0);
	return (-1);
}

int		ft_check_flag_7(char *args, char *val, char *val2)
{
	if (ft_strncmp(args, ">", ft_strlen(args)) == 0)
		return ((ft_strlen(val) > ft_strlen(val2)) ? 1 : 0);
	if (ft_strncmp(args, "<", ft_strlen(args)) == 0)
		return ((ft_strlen(val) < ft_strlen(val2)) ? 1 : 0);
	if (ft_strncmp(args, "-eq", ft_strlen(args)) == 0)
		return ((ft_atoi(val) == ft_atoi(val2)) ? 1 : 0);
	if (ft_strncmp(args, "-ne", ft_strlen(args)) == 0)
		return ((ft_atoi(val) != ft_atoi(val2)) ? 1 : 0);
	return (-1);
}

int		ft_check_flag_8(char *args, char *val, char *val2)
{
	if (ft_strncmp(args, "-gt", ft_strlen(args)) == 0)
		return ((ft_atoi(val) > ft_atoi(val2)) ? 1 : 0);
	if (ft_strncmp(args, "-ge", ft_strlen(args)) == 0)
		return ((ft_atoi(val) >= ft_atoi(val2)) ? 1 : 0);
	if (ft_strncmp(args, "-lt", ft_strlen(args)) == 0)
		return ((ft_atoi(val) < ft_atoi(val2)) ? 1 : 0);
	if (ft_strncmp(args, "-le", ft_strlen(args)) == 0)
		return ((ft_atoi(val) <= ft_atoi(val2)) ? 1 : 0);
	return (-1);
}

void	ft_free_test(char **av)
{
	int		i;

	i = 0;
	while (av[i] != NULL)
	{
		free(av[i]);
		av[i] = NULL;
		i++;
	}
	free(av);
	av = NULL;
}
