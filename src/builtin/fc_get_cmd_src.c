/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_get_cmd_src.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:43:57 by vlobunet          #+#    #+#             */
/*   Updated: 2019/05/31 15:44:00 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

void		ft_add_story(t_history **alst, t_history *new_lst)
{
	if (alst && *alst)
	{
		(*alst)->next = new_lst;
		new_lst->prev = *alst;
	}
	*alst = new_lst;
}

t_history	**get_last_cmd_history(int first, t_history **new, t_history *c)
{
	if (g_sel.story)
	{
		c = g_sel.story;
		first <= 0 ? first = g_sel.story->id : 0;
		while (c->id != first && c->id > 0)
			c = c->next;
		new = (t_history **)ft_memalloc(sizeof(t_history *));
		*new = NULL;
		ft_add_story(new, ft_lstnew_el(c->content, c->id));
		return (new);
	}
	return (NULL);
}

t_history	**min_to_max(t_param p, t_history *c, t_history **n)
{
	int	min;
	int	max;

	c = g_sel.story;
	min = ((p.first > p.last) ? p.last : p.first);
	max = ((p.first > p.last) ? p.first : p.last);
	max > c->id ? max = c->id : 0;
	while (c && c->id != min && c->id > 0)
		c = c->next;
	n = (t_history **)ft_memalloc(sizeof(t_history *));
	*n = NULL;
	while (c && c->id <= max)
	{
		ft_add_story(n, ft_lstnew_el(c->content, c->id));
		c = c->prev;
	}
	while (n && *n && (*n)->prev)
		*n = (*n)->prev;
	return (n);
}

t_history	**max_to_min(t_param p, t_history *c, t_history **n)
{
	int	min;
	int	max;

	c = g_sel.story;
	min = ((p.first > p.last) ? p.last : p.first);
	max = ((p.first > p.last) ? p.first : p.last);
	max > c->id ? max = c->id : 0;
	while (c && c->id != max)
		c = c->next;
	n = (t_history **)ft_memalloc(sizeof(t_history *));
	*n = NULL;
	while (c && c->id >= min)
	{
		ft_add_story(n, ft_lstnew_el(c->content, c->id));
		c = c->next;
	}
	while (n && *n && (*n)->prev)
		*n = (*n)->prev;
	return (n);
}

t_history	**get_cmd_history(t_param p)
{
	if ((p.first == p.last) || (p.first >= 0 && p.last < 0))
		return (get_last_cmd_history(p.first, NULL, NULL));
	if (p.l)
	{
		if ((p.first > p.last && p.r) || (p.first < p.last && !p.r))
			return (min_to_max(p, NULL, NULL));
		if ((p.first < p.last && p.r) || (p.first > p.last && !p.r) ||
			(p.first < 0 && p.last < 0))
			return (max_to_min(p, NULL, NULL));
	}
	else
	{
		if ((p.first > p.last && !p.r) || (p.first < p.last && p.r))
			return (error_get());
		if ((p.first > p.last && p.r) || (p.first < p.last && !p.r))
			return (min_to_max(p, NULL, NULL));
	}
	return (NULL);
}
