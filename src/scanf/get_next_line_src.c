/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_src.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:45:02 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 14:45:04 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_lstdel_gnl(t_gnl **cur_lst)
{
	t_gnl	*p;

	p = *cur_lst;
	(*cur_lst)->prev->next = (*cur_lst)->next;
	(*cur_lst)->next->prev = (*cur_lst)->prev;
	*cur_lst = (*cur_lst)->next;
	ft_strdel(&p->content);
	free(p);
}

t_gnl			*ft_lstnew_gnl(int fd, int buf_size)
{
	t_gnl	*lst;

	lst = (t_gnl *)malloc(sizeof(t_gnl));
	lst->fd = fd;
	lst->content = ft_strnew(buf_size);
	lst->prev = lst;
	lst->next = lst;
	return (lst);
}

void			ft_lstadd_gnl(t_gnl **alst, t_gnl *new_lst)
{
	static	t_gnl	*head;

	if (!*alst)
		*alst = new_lst;
	else
	{
		new_lst->next = (*alst)->next;
		(*alst)->next = new_lst;
		new_lst->prev = *alst;
		if (head)
			head->prev = new_lst;
	}
	if (!head)
		head = *alst;
	*alst = new_lst;
}
