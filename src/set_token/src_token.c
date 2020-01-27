/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <vlobunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 08:45:41 by vlobunet          #+#    #+#             */
/*   Updated: 2018/08/14 13:15:00 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	add_token_lst(t_token **lst_token, t_token *new)
{
	if (*lst_token)
	{
		(*lst_token)->next = new;
		new->prev = *lst_token;
	}
	*lst_token = new;
}

void	free_lst(t_token *lst)
{
	lst->next ? lst->next->prev = lst->prev : 0;
	lst->prev ? lst->prev->next = lst->next : 0;
	lst->next = NULL;
	lst->prev = NULL;
	lst->content ? ft_strdel(&lst->content) : 0;
	free(lst);
}

int		ft_is_separ(int type)
{
	if (type == 3 || type == 4 || type == 8 || type == 9)
		return (1);
	return (0);
}

int		ft_is_dir(int type)
{
	if (type == 6 || type == 7 || type == 10 || type == 11 ||
		type == 12 || type == 13 || type == 14 || type == 18 ||
		type == 19 || type == 20 || type == 21 || type == 22)
		return (1);
	return (0);
}

void	clear_token_lst(t_token **tok)
{
	t_token	*head;

	if (!tok || !*tok)
		return ;
	while (*tok && (*tok)->prev)
		*tok = (*tok)->prev;
	while ((*tok)->next)
	{
		head = (*tok)->next;
		ft_strdel(&(*tok)->content);
		(*tok)->next->prev = NULL;
		free(*tok);
		*tok = head;
	}
	ft_strdel(&(*tok)->content);
	free(*tok);
	ft_strdel(&g_sel.cmd);
	*tok = NULL;
}
