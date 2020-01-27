/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:58:57 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 18:58:59 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		handle_assign(t_tree *tmp, t_token **tokens)
{
	tmp->intvar = (t_intvar*)ft_memalloc(sizeof(t_intvar));
	if ((*tokens)->next && (*tokens)->next->type == CMD)
		tmp->intvar->exp = UNIQUE;
	else
		tmp->intvar->exp = INTERN;
	tmp->intvar->var = ft_strdup((*tokens)->content);
	tmp->intvar->next = NULL;
	*tokens = (*tokens)->next;
}

static void		handle_group(t_tree *tmp, t_token **tokens)
{
	tmp->subtree = get_subtree_as_tree(tokens);
	if (tmp->subtree->redir)
	{
		tmp->redir = tmp->subtree->redir;
		tmp->subtree->redir = NULL;
	}
	if (*tokens && (*tokens)->type == PIPE)
	{
		*tokens = remove_token(*tokens);
		tmp->command = get_pipeline(tokens);
	}
}

static int		check_tokens(t_tree *tmp, t_token **tokens)
{
	if ((*tokens)->type == CMD || (*tokens)->type == C_SUBST)
	{
		tmp->command = get_pipeline(tokens);
		tmp->token = CMD;
		return (1);
	}
	else if ((*tokens)->type == GRP)
	{
		handle_group(tmp, tokens);
		return (1);
	}
	else if ((*tokens)->type == SUBSH || (*tokens)->type == P_SUBST)
	{
		tmp->token = CMD;
		tmp->command = get_subtree_as_cmd(tokens, (*tokens)->type);
		return (1);
	}
	return (0);
}

static t_tree	*head_of_list(t_tree *head)
{
	while (head && head->father)
		head = head->father;
	return (head);
}

t_tree			*build_tree(t_tree *head, t_token **tokens)
{
	t_tree	*tmp;
	t_token	*tokenhead;

	tokenhead = find_substitutions(tokens);
	*tokens = tokenhead->next;
	while (*tokens)
	{
		if (!(tmp = (t_tree*)ft_memalloc(sizeof(t_tree))))
		{
			ft_putstr_fd("42sh: out of memory\n", STDERR_FILENO);
			run_exit(NULL);
		}
		if ((*tokens)->type == ASSIGN)
			handle_assign(tmp, tokens);
		if (*tokens)
		{
			tmp->token = (*tokens)->type;
			if (!check_tokens(tmp, tokens))
				*tokens = (*tokens)->next;
		}
		head = push_node(head, tmp);
	}
	while (tokenhead)
		tokenhead = remove_token(tokenhead);
	return (head_of_list(head));
}
