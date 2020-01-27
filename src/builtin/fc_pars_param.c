/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_pars_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:46:46 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 15:46:51 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

int	error_param(void)
{
	ft_putstr_fd("fc: ERROR : Wrong input", 2);
	ft_putstr_fd("\nusage:\n", 2);
	ft_putstr_fd("  fc [-r][-e editor] [first[last]]\n", 2);
	ft_putstr_fd("  fc -l[-nr] [first[last]] \n", 2);
	return (1);
}

int	ft_ch_sumb(char *str, char s)
{
	while (*str)
		if (s == *str++)
			return (1);
	return (0);
}

int	is_alpha_or_num(char *str, int flag)
{
	while (*str)
	{
		if (flag && *str >= 'a' && *str <= 'z')
			str++;
		else if (!flag && *str >= '0' && *str <= '9')
			str++;
		else
			return (1);
	}
	return (0);
}

int	ft_get_pr1(t_param *lst_pr, char *param, int i)
{
	while (param[i])
	{
		if (ft_ch_sumb("rnle", param[i]))
		{
			lst_pr->l = (param[i] == 'l' ? 1 : lst_pr->l);
			lst_pr->r = (param[i] == 'r' ? 1 : lst_pr->r);
			lst_pr->n = (param[i] == 'n' ? 1 : lst_pr->n);
			lst_pr->e = (param[i] == 'e' ? 1 : lst_pr->e);
			lst_pr->e = (param[i] == 'l' ? 0 : lst_pr->e);
		}
		else
			return (error_param());
		i++;
	}
	return (0);
}

int	ft_get_pr2(t_param *lst_pr, char *param)
{
	if (!is_alpha_or_num(param, 1))
	{
		if (lst_pr->e && !lst_pr->editor)
			lst_pr->editor = ft_strdup(param);
		else
			return (error_param());
	}
	else if (!is_alpha_or_num(param, 0))
	{
		if (lst_pr->first < 0)
			lst_pr->first = ft_atoi(param);
		else if (lst_pr->last < 0)
			lst_pr->last = ft_atoi(param);
		else
			return (error_param());
	}
	return (0);
}
