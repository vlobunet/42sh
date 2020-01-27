/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:32:24 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 18:32:26 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

int		check_flag(char *flag)
{
	if (ft_strcmp(flag, ">") == 0 || ft_strcmp(flag, "<") == 0 ||
		ft_strcmp(flag, "=") == 0 || ft_strcmp(flag, "!=") == 0 ||
		ft_strcmp(flag, "-b") == 0 || ft_strcmp(flag, "-c") == 0 ||
		ft_strcmp(flag, "-d") == 0 || ft_strcmp(flag, "-e") == 0 ||
		ft_strcmp(flag, "-f") == 0 || ft_strcmp(flag, "-g") == 0 ||
		ft_strcmp(flag, "-h") == 0 || ft_strcmp(flag, "-k") == 0 ||
		ft_strcmp(flag, "-n") == 0 || ft_strcmp(flag, "-p") == 0 ||
		ft_strcmp(flag, "-r") == 0 || ft_strcmp(flag, "-s") == 0 ||
		ft_strcmp(flag, "-t") == 0 || ft_strcmp(flag, "-u") == 0 ||
		ft_strcmp(flag, "-w") == 0 || ft_strcmp(flag, "-x") == 0 ||
		ft_strcmp(flag, "-z") == 0 || ft_strcmp(flag, "-L") == 0 ||
		ft_strcmp(flag, "-S") == 0 || ft_strcmp(flag, "-le") == 0 ||
		ft_strcmp(flag, "-nt") == 0 || ft_strcmp(flag, "-lt") == 0 ||
		ft_strcmp(flag, "-ot") == 0 || ft_strcmp(flag, "-ef") == 0 ||
		ft_strcmp(flag, "-eq") == 0 || ft_strcmp(flag, "-ne") == 0 ||
		ft_strcmp(flag, "-ge") == 0)
		return (1);
	return (0);
}

int		validation_flag(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		if (arg[i][0] == '-' || arg[i][0] == '=' || arg[i][0] == '!' ||
			arg[i][0] == '>' || arg[i][0] == '<')
			if (!check_flag(arg[i]))
			{
				ft_putstr_fd("test: ", 2);
				ft_putstr_fd(arg[i], 2);
				ft_putendl_fd("unary operator expected", 2);
				return (0);
			}
		i++;
	}
	return (1);
}

char	**ft_get_arguments(char **av, int size)
{
	char	**arg;
	int		i;
	int		j;

	i = -1;
	j = -1;
	arg = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	arg[size] = NULL;
	while (av[++i] != NULL)
	{
		if (av[i][0] != '-' && av[i][0] != '=' && av[i][0] != '!' &&
			av[i][0] != '>' && av[i][0] != '<')
			arg[++j] = ft_strdup(av[i]);
	}
	return (arg);
}

int		count_arguments(char **ag)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (ag[i] != NULL)
	{
		if (ag[i][0] != '-')
			count++;
		i++;
	}
	return (count);
}

int		ft_test(char **av)
{
	char	**arg;

	arg = ft_get_arguments(av, count_arguments(av));
	if (arg[1] == NULL)
		return (-1);
	if (count_arguments(av) == 2 && size_array(av) == 2)
		return (0);
	if (validation_flag(av) == 0)
	{
		ft_free_test(arg);
		return (-1);
	}
	if (make_test(av, arg) == 1)
	{
		ft_free_test(arg);
		return (0);
	}
	ft_free_test(arg);
	return (1);
}
