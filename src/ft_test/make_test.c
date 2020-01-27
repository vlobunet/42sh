/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 21:24:50 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 21:24:52 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

int		test_error_binary(char *str)
{
	ft_putstr_fd("test: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("binary operator expected", 2);
	return (0);
}

int		size_array(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

int		binary_operatir(char *flag)
{
	if (ft_strcmp(flag, "-nt") == 0 || ft_strcmp(flag, "-ot") == 0 ||
		ft_strcmp(flag, "-ef") == 0 || ft_strcmp(flag, ">") == 0 ||
		ft_strcmp(flag, "!=") == 0 || ft_strcmp(flag, "=") == 0 ||
		ft_strcmp(flag, "<") == 0 || ft_strcmp(flag, "-eq") == 0)
		return (1);
	return (0);
}

int		ft_check_flag(char *args, char *val, char *val2)
{
	int	ret;

	if ((ret = ft_check_flag_1(args, val, val2)) != -1)
		return (ret);
	if ((ret = ft_check_flag_2(args, val, val2)) != -1)
		return (ret);
	if ((ret = ft_check_flag_3(args, val, val2)) != -1)
		return (ret);
	if ((ret = ft_check_flag_4(args, val, val2)) != -1)
		return (ret);
	if ((ret = ft_check_flag_5(args, val, val2)) != -1)
		return (ret);
	if ((ret = ft_check_flag_6(args, val, val2)) != -1)
		return (ret);
	if ((ret = ft_check_flag_7(args, val, val2)) != -1)
		return (ret);
	if ((ret = ft_check_flag_8(args, val, val2)) != -1)
		return (ret);
	return (-1);
}

int		make_test(char **args, char **param)
{
	int	i;
	int	j;
	int	ret;

	i = 1;
	j = 1;
	ret = 0;
	while (args[i])
	{
		if (args[i - 1][0] == '-' && args[i][0] == '-')
			return (test_error_binary(args[i]));
		if (ft_strcmp(args[i], param[j]) == 0)
		{
			j++;
			i++;
			if (i == size_array(args))
				break ;
		}
		if (binary_operatir(args[i]))
			ret = ft_check_flag(args[i], param[j - 1], param[j]) == 1 ? 1 : -1;
		else
			ret = ft_check_flag(args[i], param[j], NULL) == 1 ? 1 : -1;
		i++;
	}
	return (ret);
}
