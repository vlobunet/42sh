/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flag_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:49:33 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 20:49:35 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

int		ft_check_flag_1(char *args, char *val, char *val2)
{
	struct stat	st;

	if (!val2)
		val2 = NULL;
	if (ft_strncmp(args, "-b", ft_strlen(args)) == 0)
		return ((stat(val, &st) == 0 && S_ISBLK(st.st_mode)) ? 1 : 0);
	if (ft_strncmp(args, "-c", ft_strlen(args)) == 0)
		return ((stat(val, &st) == 0 && S_ISCHR(st.st_mode)) ? 1 : 0);
	if (ft_strncmp(args, "-d", ft_strlen(args)) == 0)
		return ((stat(val, &st) == 0 && S_ISDIR(st.st_mode)) ? 1 : 0);
	if (ft_strncmp(args, "-e", ft_strlen(args)) == 0)
		return ((access(val, F_OK) != -1) ? 1 : 0);
	return (-1);
}

int		ft_check_flag_2(char *args, char *val, char *val2)
{
	struct stat	st;

	if (!val2)
		val2 = NULL;
	if (ft_strncmp(args, "-f", ft_strlen(args)) == 0)
		return ((stat(val, &st) == 0 && S_ISREG(st.st_mode)) ? 1 : 0);
	if (ft_strncmp(args, "-g", ft_strlen(args)) == 0)
		return ((stat(val, &st) == 0 && (st.st_gid)) ? 1 : 0);
	if (ft_strncmp(args, "-h", ft_strlen(args)) == 0)
		return ((lstat(val, &st) == 0 && (S_ISLNK(st.st_mode))) ? 1 : 0);
	if (ft_strncmp(args, "-k", ft_strlen(args)) == 0)
		return ((lstat(val, &st) == 0 && (st.st_mode & S_ISVTX)) ? 1 : 0);
	return (-1);
}

int		ft_check_flag_3(char *args, char *val, char *val2)
{
	struct stat	st;

	if (!val2)
		val2 = NULL;
	if (ft_strncmp(args, "-n", ft_strlen(args)) == 0)
		return ((ft_strlen(val) != 0) ? 1 : 0);
	if (ft_strncmp(args, "-p", ft_strlen(args)) == 0)
		return ((lstat(val, &st) == 0 && (S_ISFIFO(st.st_mode))) ? 1 : 0);
	if (ft_strncmp(args, "-r", ft_strlen(args)) == 0)
		return ((lstat(val, &st) == 0 && (st.st_mode & S_IREAD)) ? 1 : 0);
	if (ft_strncmp(args, "-s", ft_strlen(args)) == 0)
		return ((lstat(val, &st) == 0 && st.st_size > 0) ? 1 : 0);
	return (-1);
}

int		ft_check_flag_4(char *args, char *val, char *val2)
{
	struct stat	st;

	if (!val2)
		val2 = NULL;
	if (ft_strncmp(args, "-t", ft_strlen(args)) == 0)
		return ((isatty(ft_atoi(val)) == 1) ? 1 : 0);
	if (ft_strncmp(args, "-u", ft_strlen(args)) == 0)
		return ((stat(val, &st) == 0 && (st.st_uid)) ? 1 : 0);
	if (ft_strncmp(args, "-w", ft_strlen(args)) == 0)
		return ((stat(val, &st) == 0 && (st.st_mode & S_IWRITE)) ? 1 : 0);
	if (ft_strncmp(args, "-x", ft_strlen(args)) == 0)
		return ((stat(val, &st) == 0 && (st.st_mode & S_IEXEC)) ? 1 : 0);
	return (-1);
}
