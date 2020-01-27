/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:48:20 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 19:48:22 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_is_numeric(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		++str;
	}
	return (1);
}

void	redir_to_file(t_token **tk, t_cmd *cur, t_redirect *rd, t_redirect *p)
{
	rd->type = (*tk)->type;
	rd->left = ft_atoi((*tk)->content);
	*tk = remove_token(*tk);
	rd->outtype = NAME;
	rd->right.filename = ft_strdup((*tk)->content);
	*tk = remove_token(*tk);
	p = cur->redir;
	while (p && p->next)
		p = p->next;
	if (p)
	{
		p->next = (t_redirect*)ft_memalloc(sizeof(t_redirect));
		p = p->next;
	}
	else
	{
		cur->redir = (t_redirect*)ft_memalloc(sizeof(t_redirect));
		p = cur->redir;
	}
	ft_memcpy(p, rd, sizeof(t_redirect));
}

int		valid_fd(t_token **tokens, t_redirect *redir)
{
	redir->type = (*tokens)->type;
	redir->left = ft_atoi((*tokens)->content);
	(*tokens) = remove_token(*tokens);
	if (ft_strequ((*tokens)->content, "-"))
		redir->outtype = CLOSED;
	else if (ft_is_numeric((*tokens)->content))
	{
		redir->outtype = FD;
		redir->right.fd = ft_atoi((*tokens)->content);
	}
	else
	{
		ft_putstr_fd("42sh: redirection error\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	get_next(t_redirect **ptr, t_cmd **cur)
{
	if (*ptr)
	{
		(*ptr)->next = (t_redirect*)ft_memalloc(sizeof(t_redirect));
		*ptr = (*ptr)->next;
	}
	else
	{
		(*cur)->redir = (t_redirect*)ft_memalloc(sizeof(t_redirect));
		*ptr = (*cur)->redir;
	}
}

int		get_redirections(t_token **tokens, t_cmd *cur)
{
	t_redirect redir;
	t_redirect *ptr;

	redir.next = NULL;
	ptr = NULL;
	if (*tokens && ((*tokens)->type == GREAT || (*tokens)->type == LESS
		|| (*tokens)->type == GGREAT))
		redir_to_file(tokens, cur, &redir, ptr);
	else if (*tokens && ((*tokens)->type == LESSAND
		|| (*tokens)->type == GREATAND))
	{
		if (!valid_fd(tokens, &redir))
			return (0);
		*tokens = remove_token(*tokens);
		ptr = cur->redir;
		while (ptr && ptr->next)
			ptr = ptr->next;
		get_next(&ptr, &cur);
		ft_memcpy(ptr, &redir, sizeof(t_redirect));
	}
	return (1);
}
