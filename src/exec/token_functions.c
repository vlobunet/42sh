/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:37:10 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 18:37:12 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_token	*remove_token(t_token *token)
{
	t_token *next;
	t_token *prev;

	if (!token)
		return (NULL);
	prev = token->prev;
	next = token->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	ft_strdel(&token->content);
	free(token);
	token = NULL;
	return (next);
}

void	insert_token(t_token **head, char *content, int type)
{
	t_token *token;

	token = (t_token*)ft_memalloc(sizeof(t_token));
	if (!token)
	{
		ft_putstr_fd("42sh: out of memory\n", STDERR_FILENO);
		run_exit(NULL);
	}
	if (!head || !*head)
	{
		*head = token;
		return ;
	}
	token->type = type;
	token->content = ft_strdup(content);
	token->next = (*head)->next;
	if ((*head)->next)
		(*head)->next->prev = token;
	token->prev = (*head);
	(*head)->next = token;
	*head = (*head)->next;
}
