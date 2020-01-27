/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:55:38 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/06 16:55:40 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			check_assign(t_token *lookahead)
{
	if (!check_prev(lookahead))
		return (0);
	lookahead = lookahead->next;
	return (parse(lookahead, 0));
}

int			cmd_separator(t_token *lookahead)
{
	if (lookahead && lookahead->type == GRP_END)
	{
		lookahead = lookahead->next;
		if (optredir(&lookahead))
			lookahead = lookahead->next;
		if (optpipe(&lookahead))
			return (parse(lookahead, 1));
		if (match_separator(&lookahead))
			return (parse(lookahead, 0));
		return (0);
	}
	return (parse(lookahead, 0));
}

int			cmd_close_br(t_token *lookahead)
{
	lookahead = lookahead->next;
	lookahead = optargs(lookahead);
	if (optredir(&lookahead))
		lookahead = lookahead->next;
	if (optpipe(&lookahead))
		return (parse(lookahead, 1));
	if (match_separator(&lookahead))
		return (parse(lookahead, 0));
	else if (match_ctrl_operator(&lookahead))
		return (parse(lookahead, 1));
	else if (lookahead->type == GRP || lookahead->type == SUBSH
		|| lookahead->type == P_SUBST || lookahead->type == C_SUBST)
		return (parse(lookahead, 1));
	return (0);
}

int			check_cmd(t_token *lookahead)
{
	if (!check_prev(lookahead))
		return (0);
	lookahead = lookahead->next;
	lookahead = optargs(lookahead);
	if (lookahead && (lookahead->type == P_SUBST || lookahead->type == C_SUBST))
		return (parse(lookahead, 1));
	if (optredir(&lookahead))
		lookahead = lookahead->next;
	if (optpipe(&lookahead))
		return (parse(lookahead, 1));
	if (match_separator(&lookahead))
		return (cmd_separator(lookahead));
	if (lookahead && (lookahead->type == SUBSH_END ||
		lookahead->type == P_SUBST_END || lookahead->type == C_SUBST_END))
	{
		return (cmd_close_br(lookahead));
	}
	else if (lookahead && match_ctrl_operator(&lookahead))
		return (parse(lookahead, 1));
	else
		return (0);
}

int			parse(t_token *lookahead, int cmd)
{
	if (lookahead != NULL)
	{
		if (lookahead->type == ASSIGN)
			return (check_assign(lookahead));
		if (lookahead && lookahead->type == CMD)
			return (check_cmd(lookahead));
		else if (lookahead->type == GRP || lookahead->type == SUBSH ||
			lookahead->type == P_SUBST || lookahead->type == C_SUBST)
		{
			lookahead = lookahead->next;
			return (parse(lookahead, 1));
		}
		else if (lookahead->prev && (lookahead->type == AND ||
			lookahead->type == OR))
		{
			lookahead = lookahead->next;
			return (parse(lookahead, 1));
		}
		else if (match_separator(&lookahead))
			return (parse(lookahead, 0));
		return (0);
	}
	if (cmd)
		return (0);
	return (1);
}
