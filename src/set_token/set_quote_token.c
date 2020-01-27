/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:15:37 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/02 18:24:07 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		check_content(char *content, char symbol_1, char symbol_2)
{
	if ((content && symbol_1 == '"' && ft_strchr(content, '`')) ||
			(symbol_1 == '`' && symbol_2 != '\0'))
		return (1);
	return (0);
}

static void		set_tmp_content(char **content, char *tmp)
{
	tmp = ft_strndup((*content) + 1, ft_strlen(*content) - 2);
	ft_strdel(content);
	*content = ft_strdup(tmp);
	ft_strdel(&tmp);
}

static void		fast_forward(t_token **cur, t_token *del)
{
	while ((*cur)->next)
		*cur = (*cur)->next;
	(*cur)->next = del->next;
	del->next ? del->next->prev = *cur : 0;
	ft_strdel(&del->content);
	free(del);
}

static t_token	*cut_backquote(t_token **cur, t_helper h,
	t_token *t, t_token **tok)
{
	t_token *del;

	while ((*cur)->content[h.i] && (*cur)->content[h.i] != '`')
		h.i = h.i + ((*cur)->content[h.i] == '\\'
			&& (*cur)->content[h.i + 1] ? 2 : 1);
	if ((*cur)->content[h.i] == '`')
	{
		h.start = h.i;
		h.i++;
		while ((*cur)->content[h.i] && (*cur)->content[h.i] != '`')
			h.i = h.i + ((*cur)->content[h.i] == '\\'
				&& (*cur)->content[h.i + 1] ? 2 : 1);
		h.end = h.i;
		h.i++;
		t = create_new_token_line(h.start, h.end, (*cur)->content);
		del = *cur;
		!(*cur)->prev ? *tok = t : 0;
		t->prev = (*cur)->prev;
		(*cur)->prev ? (*cur)->prev->next = t : 0;
		*cur = t;
		fast_forward(cur, del);
	}
	return ((*cur)->next);
}

void			set_quote_token(t_token **tok, t_token *cur)
{
	t_helper	h;
	char		*tmp;

	cur = *tok;
	h.start = 0;
	h.end = 0;
	tmp = NULL;
	while (cur)
	{
		if (check_content(cur->content, cur->content[0], cur->content[2]))
		{
			h.i = 0;
			cur = cut_backquote(&cur, h, NULL, tok);
		}
		else
		{
			if (cur->content && (cur->content[0] == '"'))
				set_tmp_content(&cur->content, tmp);
			cur = cur->next;
		}
	}
}
