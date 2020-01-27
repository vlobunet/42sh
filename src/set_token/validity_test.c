/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <vlobunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 08:46:03 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 18:12:59 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		count_char(char *s)
{
	int len;
	int ln;

	if (!s)
		return (0);
	ln = ft_strlen(s);
	len = 0;
	while (ln - len >= 0 && s[ln - len] == '\\')
		len += 1;
	return (len);
}

int		is_new_prompt(t_token *prev)
{
	if (prev)
	{
		if (!(prev = prev->next))
			return (1);
		if (ft_is_dir(prev->type))
			return (ft_err_message("newline"));
		if ((ft_is_separ(prev->type) && prev->type != 3) ||
			(count_char(prev->content) % 2 == 1))
			return (-3);
	}
	return (1);
}

int		not_ended(t_token *tmp)
{
	if (tmp && !tmp->next)
	{
		if (tmp->type == PIPE || tmp->type == OR || tmp->type == AND)
		{
			ft_strdel(&g_sel.cmd);
			return (1);
		}
	}
	return (0);
}

int		ft_is_error(t_token *tmp, t_token *prev, int *open_br)
{
	if (tmp && tmp->type == 3 && (!prev || prev->type == 3))
		return (0);
	if (tmp && (tmp->type == ASSIGN || tmp->type == C_SUBST
			|| tmp->type == C_SUBST_END))
		return (0);
	if (tmp && (tmp->type == SUBSH || tmp->type == GRP))
	{
		++*open_br;
		return (0);
	}
	if (tmp && (tmp->type == SUBSH_END || tmp->type == GRP_END))
	{
		--*open_br;
		return (0);
	}
	if (tmp && ((tmp->type != 1 && !prev) || not_ended(tmp)))
		return (ft_err_message(""));
	if (tmp && (tmp->type == 1 && !tmp->content && !tmp->content[0]))
		return (ft_err_message("Command not found"));
	if (ft_is_separ(tmp->type) && (!prev || ft_is_separ(prev->type) ||
		ft_is_dir(prev->type)))
		return (ft_err_message(tmp->content));
	if (ft_is_dir(tmp->type) && (prev && ft_is_dir(prev->type)))
		return (ft_err_message(tmp->content));
	return (0);
}

int		validity_test(t_token **lst, t_token *tmp, t_token *prev)
{
	int		ret;
	int		open_br;

	open_br = 0;
	if (!lst && !*lst)
		return (0);
	tmp = *lst;
	while (tmp)
	{
		prev = tmp->prev;
		if ((ret = ft_is_error(tmp, prev, &open_br)))
			return (ret);
		tmp = tmp->next;
	}
	if (open_br)
		return (-1);
	if (!prev && (count_char((*lst)->content) % 2 == 1))
		return (-3);
	return (is_new_prompt(prev));
}
