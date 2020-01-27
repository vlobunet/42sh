/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_alias_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:22:11 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 18:22:14 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_del_tok(t_token *del)
{
	ft_strdel(&(del->content));
	free(del);
	del = NULL;
}

void	get_alias_tok(t_token ***hed, t_alias *alias)
{
	t_token *n;
	t_token *tmp;

	n = NULL;
	tmp = NULL;
	while (alias && ft_strcmp((**hed)->content, alias->name))
		alias = alias->next;
	if (alias && !ft_strcmp((**hed)->content, alias->name))
	{
		token_main(alias->value, &n, 1, 0);
		free((**hed)->content);
		(**hed)->content = ft_strdup(n->content);
		(**hed)->type = n->type;
		tmp = (**hed)->next;
		(**hed)->next = n->next;
		n->next->prev = **hed;
		ft_del_tok(n);
		while ((**hed)->next)
			(**hed) = (**hed)->next;
		(**hed)->next = tmp;
		tmp ? tmp->prev = (**hed) : 0;
	}
}

void	set_alias(t_token **hed)
{
	t_token *p;

	p = NULL;
	p = *hed;
	while (hed && *hed)
	{
		if ((*hed)->type == 1)
			get_alias_tok(&hed, g_sel.alias);
		*hed = (*hed)->next;
	}
	*hed = p;
}
