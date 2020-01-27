/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 20:31:26 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 20:31:28 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	redir_to_pipe(t_token *token)
{
	token->next = (t_token*)ft_memalloc(sizeof(t_token));
	token->next->type = GREATAND;
	token->next->content = ft_strdup("1");
	token->next->prev = token;
	token->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	token->next->next->type = TARGET;
	token->next->next->prev = token->next;
	token->next->next->next = NULL;
}

char	*run_subtree_to_pipe(t_token *tkn, int *fds, t_token *lst, t_tree *tree)
{
	t_cmd	*subst;
	char	*fd;
	char	*retstr;

	fd = ft_itoa(fds[1]);
	tkn->next->next->content = fd;
	subst = get_subtree_as_cmd(&lst, P_SUBST);
	tree->token = CMD;
	tree->command = subst;
	fd = ft_itoa(fds[0]);
	retstr = ft_strjoin("/dev/fd/", fd);
	free(fd);
	run_tree(tree, 0, 0);
	close(fds[1]);
	destruction_tree(subst->subtree);
	return (retstr);
}

char	*substitute_process(t_token **tokens, t_token *token)
{
	t_token	*list;
	t_token	*end;
	int		fds[2];
	char	*retstr;
	t_tree	*tree;

	tree = (t_tree*)ft_memalloc(sizeof(t_tree));
	list = token;
	while (token && token->type != P_SUBST_END)
		token = token->next;
	end = token->next;
	redir_to_pipe(token);
	pipe(fds);
	retstr = run_subtree_to_pipe(token, fds, list, tree);
	destruction_tree(tree);
	*tokens = end;
	return (retstr);
}
