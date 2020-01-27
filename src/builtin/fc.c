/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:40:43 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 15:40:47 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

void	print_list_history(t_param p, t_history **cmd)
{
	while (cmd && *cmd)
	{
		if (!p.n)
		{
			ft_putstr_fd("[", 1);
			ft_putnbr_fd((*cmd)->id, 1);
			ft_putstr_fd("].\t", 1);
		}
		ft_putendl_fd((*cmd)->content, 1);
		*cmd = (*cmd)->next;
	}
}

int		run_fc(char **param)
{
	t_param		lst_pr;
	int			i;
	int			res;
	t_history	**cmd;

	i = 1;
	res = 0;
	lst_pr = (t_param){0, 0, 0, -1, -1, 0, NULL};
	while (param && param[i] && param[i][0] == '-' && !res)
		if (!(res = ft_get_pr1(&lst_pr, param[i], 1)))
			i++;
	while (param && param[i] && !res)
		if (!(res = ft_get_pr2(&lst_pr, param[i])))
			i++;
	if ((cmd = get_cmd_history(lst_pr)))
	{
		lst_pr.l ? print_list_history(lst_pr, cmd) : 0;
		!lst_pr.l ? print_command_editor(lst_pr, cmd, 0) : 0;
	}
	return (1);
}
