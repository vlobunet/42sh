/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:14:32 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 19:14:34 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_freecmdlist(t_cmd *list)
{
	t_cmd *prev;

	while (list)
	{
		prev = list;
		list = list->next;
		ft_strdel(&prev->path);
		if (prev->av)
			ft_freestrarr(prev->av);
		ft_freeredirections(prev);
		free(prev);
		prev = NULL;
	}
}

void	destruction_tree(t_tree *root)
{
	if (root == NULL)
		return ;
	if (root->left)
		destruction_tree(root->left);
	if (root->right)
		destruction_tree(root->right);
	if (root->command && !root->command->pid && !root->command->state)
		ft_freecmdlist(root->command);
	if (root->intvar)
	{
		ft_strdel(&root->intvar->var);
		free(root->intvar);
		root->intvar = NULL;
	}
	free(root);
	root = NULL;
	return ;
}

int		tkn_priority(int token)
{
	if (token == CMD || token == GRP || token == ASSIGN)
		return (1);
	else if (token == AND || token == OR)
		return (2);
	else if (token == SEMI || token == BG)
		return (3);
	return (0);
}

void	set_node(t_tree *head, t_tree *node)
{
	t_tree *tmp;

	tmp = head->father;
	head->father = node;
	node->left = head;
	node->father = tmp;
	if (tmp)
		tmp->right = node;
}

t_tree	*push_node(t_tree *head, t_tree *node)
{
	node->father = NULL;
	node->left = NULL;
	node->right = NULL;
	if (!head)
	{
		head = node;
		return (node);
	}
	if (tkn_priority(node->token) > tkn_priority(head->token))
	{
		while (head->father && tkn_priority(head->token)
			<= tkn_priority(node->token))
			head = head->father;
		set_node(head, node);
	}
	else
	{
		node->father = head;
		head->right = node;
	}
	return (node);
}
