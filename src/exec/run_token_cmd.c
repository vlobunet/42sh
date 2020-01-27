/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_token_cmd_cp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:30:38 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 18:30:40 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		check_prev(t_token *lookahead)
{
	if (!lookahead)
		return (0);
	if (lookahead->prev && (lookahead->prev->type == CMD ||
		lookahead->prev->type == SUBSH_END || lookahead->prev->type == GRP_END))
		return (0);
	return (1);
}

int		check_pipelines(t_token *tok)
{
	t_token *lookahead;

	lookahead = tok;
	return (parse(lookahead, 0));
}

int		run_token_cmd(t_token **tok)
{
	t_tree	*ast;
	t_token	*tmp;
	int		ret;

	ast = NULL;
	if (!tok || !*tok)
		return (0);
	tmp = *tok;
	ret = check_pipelines(tmp);
	if (!ret)
	{
		ft_putstr_fd("42sh: Parse error\n", STDERR_FILENO);
		return (0);
	}
	ast = build_tree(ast, tok);
	run_tree(ast, 0, 0);
	g_sel.fd[0] = dup(0);
	g_sel.fd[1] = dup(1);
	g_sel.fd[2] = dup(2);
	destruction_tree(ast);
	return (0);
}
