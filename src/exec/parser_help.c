/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:56:14 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/06 16:56:16 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_token		*optargs(t_token *lookahead)
{
	if (lookahead)
	{
		if (lookahead->type == ARG)
		{
			while (lookahead && lookahead->type == ARG)
				lookahead = lookahead->next;
		}
	}
	return (lookahead);
}

int			optpipe(t_token **lookahead)
{
	if (*lookahead)
	{
		if ((*lookahead)->type == PIPE)
		{
			*lookahead = (*lookahead)->next;
			return (1);
		}
	}
	return (0);
}

int			optredir(t_token **lhd)
{
	if (*lhd)
	{
		while (1)
		{
			if ((*lhd)->type == LESS || (*lhd)->type == GREAT
				|| (*lhd)->type == GGREAT ||
				(*lhd)->type == GREATAND || (*lhd)->type == LESSAND)
			{
				*lhd = (*lhd)->next;
				if (!*lhd || (*lhd)->type != TARGET)
					return (0);
				if (*lhd && (*lhd)->next && ((*lhd)->next->type == LESS
					|| (*lhd)->next->type == GREAT || (*lhd)->next->type
					== GGREAT || (*lhd)->next->type == GREATAND ||
					(*lhd)->next->type == LESSAND))
				{
					*lhd = (*lhd)->next;
					continue ;
				}
				return (1);
			}
			return (0);
		}
	}
	return (0);
}

int			match_separator(t_token **lookahead)
{
	if (*lookahead)
	{
		if ((*lookahead)->type != SEMI && (*lookahead)->type != BG)
			return (0);
		*lookahead = (*lookahead)->next;
	}
	return (1);
}

int			match_ctrl_operator(t_token **lookahead)
{
	if (*lookahead)
	{
		if ((*lookahead)->type != OR && (*lookahead)->type != AND)
			return (0);
		*lookahead = (*lookahead)->next;
		return (1);
	}
	return (0);
}
