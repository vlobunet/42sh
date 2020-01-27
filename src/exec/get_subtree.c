/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subtree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:22:35 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 19:22:37 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	cut_tree_sublist(t_token *tmp, t_token *end, t_token **tokens)
{
	while (tmp && tmp->type != GRP_END)
		tmp = tmp->next;
	end = tmp->prev;
	(*tokens)->next = tmp;
	tmp->prev = (*tokens);
	*tokens = remove_token(*tokens);
	*tokens = remove_token(*tokens);
	end->next = NULL;
}

t_tree		*get_subtree_as_tree(t_token **tokens)
{
	t_tree	*tree;
	t_token	*sublist;
	t_token	*tmp;
	t_token	*end;
	t_cmd	*cmd;

	tree = NULL;
	end = NULL;
	sublist = (*tokens)->next;
	tmp = sublist;
	cut_tree_sublist(tmp, end, tokens);
	tree = build_tree(tree, &sublist);
	while (sublist)
		sublist = remove_token(sublist);
	cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd));
	if (!cmd)
	{
		ft_putstr_fd("42sh: out of memory\n", STDERR_FILENO);
		run_exit(NULL);
	}
	get_redirections(tokens, cmd);
	tree->redir = cmd->redir;
	free(cmd);
	return (tree);
}

static void	cut_cmd_sublist(t_token **tkn, t_token *tmp, t_token *end, int tok)
{
	while (tmp && tmp->type != (tok + 1))
		tmp = tmp->next;
	end = tmp->prev;
	(*tkn)->next = tmp;
	tmp->prev = (*tkn);
	*tkn = remove_token(*tkn);
	*tkn = remove_token(*tkn);
	end->next = NULL;
}

static void	init_cmd(t_cmd *cmd)
{
	if (!cmd)
	{
		ft_putstr_fd("42sh: out of memory\n", STDERR_FILENO);
		run_exit(NULL);
	}
	cmd->out_fd = STDOUT_FILENO;
	cmd->cmd_type = SUBSHELL;
}

t_cmd		*get_subtree_as_cmd(t_token **tokens, int tok)
{
	t_cmd	*cmd;
	t_token	*sublist;
	t_token	*tmp;
	t_token	*end;
	t_cmd	*tmpc;

	end = NULL;
	cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd));
	init_cmd(cmd);
	sublist = (*tokens)->next;
	tmp = sublist;
	cut_cmd_sublist(tokens, tmp, end, tok);
	cmd->subtree = build_tree(cmd->subtree, &sublist);
	while (sublist)
		sublist = remove_token(sublist);
	get_redirections(tokens, cmd);
	if (tok != C_SUBST && *tokens && (*tokens)->type == PIPE)
	{
		*tokens = remove_token(*tokens);
		tmpc = get_pipeline(tokens);
		cmd->next = tmpc;
		tmpc->prev = cmd;
	}
	return (cmd);
}
