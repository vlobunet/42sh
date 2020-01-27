/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity_test_src.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <vlobunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 19:32:28 by vlobunet          #+#    #+#             */
/*   Updated: 2018/08/15 19:33:14 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	add_token(t_token **lst_token, t_token *new)
{
	if (*lst_token)
	{
		new->next = (*lst_token)->next;
		new->prev = *lst_token;
		(*lst_token)->next ? (*lst_token)->next->prev = new : 0;
		(*lst_token)->next = new;
	}
	*lst_token = new;
}

void	split_token(t_token *t, char **cmd)
{
	int		i;

	t = t->prev;
	i = -1;
	free_lst(t->next);
	while (cmd[++i])
		add_token(&t, creat_token(cmd[i], (int)ft_strlen(cmd[i]), NULL));
	ft_freestrarr(cmd);
}

void	divide_the_string(t_token *t, char *tmp, char **cmd, int *i)
{
	i[0] = -1;
	i[2] = (int)ft_strlen(t->content);
	tmp = ft_strndup(t->content + 1, i[2] - 2);
	cmd = ft_strsplit(tmp, '\n');
	ft_strdel(&tmp);
	while (cmd[++i[0]])
	{
		i[1] = -1;
		tmp = ft_strnew((int)ft_strlen(cmd[i[0]]) + 3);
		tmp[0] = '`';
		while (cmd[i[0]] && cmd[i[0]][++i[1]])
			tmp[i[1] + 1] = cmd[i[0]][i[1]];
		tmp[i[1] + 1] = '`';
		tmp[i[1] + 2] = 0;
		ft_strdel(&cmd[i[0]]);
		cmd[i[0]] = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	split_token(t, cmd);
}
