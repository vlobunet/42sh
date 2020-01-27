/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <vlobunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 10:26:26 by vlobunet          #+#    #+#             */
/*   Updated: 2018/08/12 15:57:46 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_history	*ft_lstnew_el(char *cmd, int id)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	new->prev = NULL;
	new->next = NULL;
	new->content = ft_strdup(cmd);
	new->id = id;
	return (new);
}

void		ft_lstdel_all(t_list **lst)
{
	t_list	*tmp;

	while (*lst && (*lst)->prev)
		*lst = (*lst)->prev;
	while (*lst && (*lst)->next)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		tmp->content ? ft_strdel(&tmp->content) : 0;
		tmp->name ? ft_strdel(&tmp->name) : 0;
		tmp->next->prev = NULL;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
	}
	if (*lst)
	{
		(*lst)->content ? ft_strdel(&(*lst)->content) : 0;
		(*lst)->name ? ft_strdel(&(*lst)->name) : 0;
		(*lst)->next = NULL;
		(*lst)->prev = NULL;
		free((*lst));
	}
}

void		ft_tokdel_all(t_token **lst)
{
	t_token *tmp;

	while (*lst && (*lst)->prev)
		*lst = (*lst)->prev;
	while (*lst && (*lst)->next)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		tmp->content ? ft_strdel(&tmp->content) : 0;
		tmp->next->prev = NULL;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
	}
	if (*lst)
	{
		(*lst)->content ? ft_strdel(&(*lst)->content) : 0;
		(*lst)->next = NULL;
		(*lst)->prev = NULL;
		free((*lst));
	}
}

t_list		*ft_lstnew(char *name, char *path)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	lst->name = ft_strdup(name);
	lst->content = ft_strdup(path);
	lst->size = (int)ft_strlen(name);
	lst->prev = NULL;
	lst->next = NULL;
	return (lst);
}

void		ft_lstadd(t_list **alst, t_list *new_lst)
{
	if (*alst)
	{
		(*alst)->next = new_lst;
		new_lst->prev = *alst;
	}
	*alst = new_lst;
}
